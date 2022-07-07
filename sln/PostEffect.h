#pragma once
#include "Sprite.h"
#include "SpriteBase.h"
#include "PipelineSet.h"

// Microsoft::WRL::を省略
template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMMATRIX = DirectX::XMMATRIX;

class PostEffect :
	public Sprite
{
public:
	static PostEffect* GetInstance();

	/// <summary>
	/// 描画コマンドの発行
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void Draw();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

private:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PostEffect();

public:
	//ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }



	//シーン描画前処理
	void PreDrawScene(ID3D12GraphicsCommandList* commandList);
	//シーン描画後処理
	void PostDrawScene(ID3D12GraphicsCommandList* commandList);

	static void SetDevice(ID3D12Device* device);

	//画面クリアカラー
	static const float clearColor[4];

private:

	static ID3D12Device* device_;

	//テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff_;
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	//深度バッファ
	ComPtr<ID3D12Resource>depthBuff;
	//RTV用デスクリプタテーブル
	ComPtr<ID3D12DescriptorHeap>descHeapRTV;
	//DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap>descHeapDSV;

	//借りるコマンドリスト
	//ID3D12GraphicsCommandList* commandList_ = nullptr;

	// テクスチャ用デスクリプタヒープの生成
	//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;

	// パイプラインセット
	//PipelineSet pipelineSet;
};