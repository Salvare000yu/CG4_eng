#include "TitleScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "GamePlayScene.h"

void TitleScene::Initialize()
{
#pragma region 描画初期化処理

    ////---objからモデルデータ読み込み---
    //model_1 = Model::LoadFromOBJ("ground");
    //model_2 = Model::LoadFromOBJ("triangle_mat");
    ////Model* model_3 = Model::LoadFromOBJ("chr_sword");
    ////---3dオブジェクト生成---
    //object3d_1 = Object3d::Create();
    //object3d_2 = Object3d::Create();
    //object3d_3 = Object3d::Create();
    ////---3dオブジェクトに3dモデルを紐づける---
    //object3d_1->SetModel(model_1);
    //object3d_2->SetModel(model_2);
    //object3d_3->SetModel(model_2);

    //object3d_2->SetScale({ 20.0f, 20.0f, 20.0f });
    //object3d_3->SetScale({ 30.0f, 30.0f, 30.0f });

    //object3d_2->SetPosition({ 5,-1,5 });
    //object3d_3->SetPosition({ -5,-1,5 });

    // 音声読み込み
    //Audio::GetInstance()->LoadWave("Alarm01.wav");

    // 音声再生
    //Audio::GetInstance()->PlayWave("Alarm01.wav");//あってる？

    // 3Dオブジェクトの数
    //const int OBJECT_NUM = 2;

    //Object3d object3ds[OBJECT_NUM];

    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title_prac.png");

    // スプライトの生成
    sprite = Sprite::Create(1, { 0,0 }, false, false);
    //for (int i = 0; i < 1; i++)
    //{
    //    int texNumber = 1;
    //    Sprite* sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

    //    // スプライトの座標変更
    //    sprite->SetPosition({ (float)(80),(float)(20),0 });
    //    //sprite->SetRotation((float)(rand() % 360));
    //    sprite->SetSize({ (float)(200), (float)(200) });

    //    sprite->TransferVertexBuffer();

    //    sprites.push_back(sprite);
    //}

#pragma endregion 描画初期化処理

    int counter = 0; // アニメーションの経過時間カウンター
}

void TitleScene::Finalize()
{

    //スプライト解放
    delete sprite;

    //3dオブジェクト解放
    //delete object3d_1;
    //delete object3d_2;
    //delete object3d_3;
    //delete model_1;
    //delete model_2;
}

void TitleScene::Update()
{
    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    if (input->TriggerKey(DIK_SPACE))     // スペースキーが押されていたら
    {
        //シーン切り替え
        BaseScene* scene = new GamePlayScene();
        sceneManager_->SetNextScene(scene);
    }

    // 座標操作
    if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
    {

    }


    if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
    {

    }

 /*   DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
    DebugText::GetInstance()->Print("nihon kougakuin!", 200, 200, 2.0f);*/

    ////3dobj
    //object3d_1->Update();
    //object3d_2->Update();
    //object3d_3->Update();

    //スプライト更新
    sprite->Update();
}

void TitleScene::Draw()
{
    //// スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDraw();
    //SpriteCommonBeginDraw(spriteCommon, dxCommon->GetCmdList());
    //// スプライト描画
    sprite->Draw();

    ////3dオブジェ描画前処理
    //Object3d::PreDraw();

    ////3dオブジェ描画
    //object3d_1->Draw();
    //object3d_2->Draw();
    //object3d_3->Draw();

    ////3dオブジェ描画後処理
    //Object3d::PostDraw();

    // ４．描画コマンドここから

    //for (int i = 0; i < _countof(object3ds); i++)
    //{
    //    DrawObject3d(&object3ds[i], dxCommon->GetCmdList(), basicDescHeap.Get(), vbView, ibView,
    //        CD3DX12_GPU_DESCRIPTOR_HANDLE(basicDescHeap->GetGPUDescriptorHandleForHeapStart(), constantBufferNum, dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)),
    //        indices, _countof(indices));
    //}

    //// スプライト共通コマンド
    //SpriteCommon::GetInstance()->PreDraw();
    //SpriteCommonBeginDraw(spriteCommon, dxCommon->GetCmdList());
    //// スプライト描画
    //sprite->Draw();
}

void TitleScene::DrawUI()
{
}
