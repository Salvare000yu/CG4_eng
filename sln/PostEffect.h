//#pragma once
//#include "Sprite.h"
//#include "SpriteCommon.h"
//#include "PipelineSet.h"
//
//class PostEffect :
//	public Sprite
//{
//public:
//
//	/// <summary>
//	/// コンストラクタ
//	/// </summary>
//	PostEffect();
//
//	/// <summary>
//	/// 描画コマンドの発行
//	/// </summary>
//	/// <param name="cmdList">コマンドリスト</param>
//	void Draw(ID3D12GraphicsCommandList* cmdList);
//
//	ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }
//
//private:
//	//借りるコマンドリスト
//	ID3D12GraphicsCommandList* commandList_ = nullptr;
//
//	// テクスチャ用デスクリプタヒープの生成
//	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
//
//	// パイプラインセット
//	PipelineSet pipelineSet;
//};