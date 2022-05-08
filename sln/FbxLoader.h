#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>

#include <string>

#include "FbxModel.h"

class FbxLoader
{
private:
	//std省略
	using string = std::string;

public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
/// ファイルからFBXモデル読み込み
/// </summary>
	void LoadModelFromFile(const string& modelName);

/// <summary>
/// 再帰的にノード構成を解析
/// </summary>　
	void ParseNodeRecursive(FbxModel* fbxModel, FbxNode* fbxNode,Node* parent=nullptr);

private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	//d3d12デバイス
	ID3D12Device* device = nullptr;
	//fbxマネージャー
	FbxManager* fbxManager = nullptr;
	//fbxインポータ
	FbxImporter* fbxImporter = nullptr;

public:

	//モデル格納ルートパス
	static const string baseDirectory;


};