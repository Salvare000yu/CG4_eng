#include "PostEffect.h"
#include <d3dx12.h>
#include "WinApp.h"

using namespace DirectX;

PostEffect::PostEffect()
    : Sprite(
        100,					//テクスチャ番号
        { 0, 0 ,0},					//座標
        { 500.0f, 500.0f },		//サイズ
        { 1, 1, 1, 1 },			//色
        { 0.0f, 0.0f },			//アンカーポイント
        false,					//左右反転フラグ
        false)					//上下反転フラグ
{
}

void PostEffect::Draw()
{
    if (isInvisible) {
        return;
    }

    SpriteCommon* spriteCommon = SpriteCommon::GetInstance();

    ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();



    //commandList_ = commandList;
    //// パイプラインステートの設定
    //commandList_->SetPipelineState(pipelineSet.pipelinestate.Get());
    //// ルートシグネチャの設定
    //commandList_->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
    //// プリミティブ形状を設定
    //commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    //spriteCommon->PreDraw();

    //// テクスチャ用デスクリプタヒープの設定
    //ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
    //commandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);



    // 頂点バッファをセット
    commandList->IASetVertexBuffers(0, 1, &vbView_);

    // ルートパラメータ0番に定数バッファをセット
    commandList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

    // ルートパラメータ1番に シェーダリソースビューをセット
    spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);

    // ポリゴンの描画（4頂点で四角形）
    commandList->DrawInstanced(4, 1, 0, 0);
}

//void PostEffect::Initialize()
//{
//    HRESULT result = S_FALSE;
//
//    SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
//
//    //基底クラスとして初期化
//    Sprite::Initialize();
//
//    //テクスチャリソース設定
//    D3D12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
//        DXGI_FORMAT_R8G8B8A8_UNORM,
//        WinApp::window_width,
//        (UINT)WinApp::window_height,
//        1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
//    );
//
//    //テクスチャバッファの生成
//    result = spriteCommon->GetDevice()->CreateCommittedResource(
//        &CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
//            D3D12_MEMORY_POOL_L0),
//        D3D12_HEAP_FLAG_NONE,
//        &texresDesc,
//        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
//        nullptr,
//        IID_PPV_ARGS(&texBuff));
//    assert(SUCCEEDED(result));
//
//}
