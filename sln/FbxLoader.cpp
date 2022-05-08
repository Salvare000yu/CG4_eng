﻿#include "FbxLoader.h"
#include <cassert>

using namespace DirectX;

//静的メンバ変数の実態
const std::string FbxLoader::baseDirectory = "Resources/";

FbxLoader* FbxLoader::GetInstance()
{
    static FbxLoader instance;
    return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device)
{
    //再初期化チェック
    assert(fbxManager == nullptr);
    //引数からメンバ変数に代入
    this->device = device;
    //fbxマネージャーの生成
    fbxManager = FbxManager::Create();
    //Fbxマネージャの入出力設定
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);
    //fbxインポータの生成
    fbxImporter = FbxImporter::Create(fbxManager, "");
}

void FbxLoader::Finalize()
{
    //各種FBXインスタンス破棄
    fbxImporter->Destroy();
    fbxManager->Destroy();
}

void FbxLoader::LoadModelFromFile(const string& modelName)
{
    //モデルと同じ名前のフォルダから読み込み
    const string directoryPath = baseDirectory +
        modelName + "/";
    //拡張子.fbx追加
    const string fileName = modelName + ".fbx";
    //連結してフルパスを得る
    const string fullpath = directoryPath + fileName;

    //ファイル名指定、FBXファイル読み込み
    if (!fbxImporter->Initialize(fullpath.c_str(),
        -1, fbxManager->GetIOSettings())) {
        assert(0);
    }

    //シーン生成
    FbxScene* fbxScene =
    FbxScene::Create(fbxManager, "fbxScene");

    //ファイルからロードしたFBXの情報をシーンにインポート
    fbxImporter->Import(fbxScene);

    //モデル生成
    FbxModel* fbxModel = new FbxModel();
    fbxModel->name = modelName;
    //fbxノード数取得
    int nodeCount = fbxScene->GetNodeCount();
    //必要分メモリ確保しといてアドレスズレないようにする
    fbxModel->nodes.reserve(nodeCount);
    //ルートノードから順に解析してモデルに流す
    ParseNodeRecursive(fbxModel, fbxScene->GetRootNode());
    //Fbxシーン解放
    fbxScene->Destroy();
}

void FbxLoader::ParseNodeRecursive(FbxModel* fbxModel, FbxNode* fbxNode,Node* parent)
{
    //ノード名取得
    string name = fbxNode->GetName();
    //モデルにノード追加
    fbxModel->nodes.emplace_back();
    Node& node = fbxModel->nodes.back();
    //fbxノードのローカル移動情報
    FbxDouble3 rotation = fbxNode->LclRotation.Get();
    FbxDouble3 scaling = fbxNode->LclScaling.Get();
    FbxDouble3 translation = fbxNode->LclTranslation.Get();
    //形式変換して代入
    node.rotation = { (float)rotation[0],(float)rotation[1],(float)rotation[2],0.0f };
    node.scaling = { (float)scaling[0],(float)scaling[1],(float)scaling[2],0.0f };
    node.translation = { (float)translation[0],(float)translation[1],(float)translation[2],1.0f };
    //回転角をdegreeからラジアンに
    node.rotation.m128_f32[0] = XMConvertToRadians(node.rotation.m128_f32[0]);
    node.rotation.m128_f32[1] = XMConvertToRadians(node.rotation.m128_f32[1]);
    node.rotation.m128_f32[2] = XMConvertToRadians(node.rotation.m128_f32[2]);
    //スケール回転平行移動計算
    XMMATRIX matScaling, matRotation, matTranslation;
    matScaling = XMMatrixScalingFromVector(node.scaling);
    matRotation = XMMatrixRotationRollPitchYawFromVector(node.rotation);
    matTranslation = XMMatrixTranslationFromVector(node.translation);
    //ローカル変形行列計算
    node.transform = XMMatrixIdentity();
    node.transform *= matScaling;//ワールド行列にスケーリング反映
    node.transform *= matRotation;//ワールド行列に回転反映
    node.transform *= matTranslation;//ワールド行列に平行移動反映
    //グローバル変形行列計算
    node.globalTransform = node.transform;
    if (parent) {
        node.parent = parent;
        //親変形を乗算
        node.globalTransform *= parent->globalTransform;
    }
    //FBXノードメッシュ情報解析

    //子ノードに対して再帰呼び出し
    for (int i = 0; i < fbxNode->GetChildCount(); i++) {
        ParseNodeRecursive(fbxModel, fbxNode->GetChild(i),&node);
    }
}