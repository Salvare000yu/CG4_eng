#include "PostEffect.h"
#include <d3dx12.h>
#include "WinApp.h"

using namespace DirectX;

PostEffect::PostEffect()
    : Sprite(
        100,					//�e�N�X�`���ԍ�
        { 0, 0 ,0},					//���W
        { 500.0f, 500.0f },		//�T�C�Y
        { 1, 1, 1, 1 },			//�F
        { 0.0f, 0.0f },			//�A���J�[�|�C���g
        false,					//���E���]�t���O
        false)					//�㉺���]�t���O
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
    //// �p�C�v���C���X�e�[�g�̐ݒ�
    //commandList_->SetPipelineState(pipelineSet.pipelinestate.Get());
    //// ���[�g�V�O�l�`���̐ݒ�
    //commandList_->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
    //// �v���~�e�B�u�`���ݒ�
    //commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    //spriteCommon->PreDraw();

    //// �e�N�X�`���p�f�X�N���v�^�q�[�v�̐ݒ�
    //ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
    //commandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);



    // ���_�o�b�t�@���Z�b�g
    commandList->IASetVertexBuffers(0, 1, &vbView_);

    // ���[�g�p�����[�^0�Ԃɒ萔�o�b�t�@���Z�b�g
    commandList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

    // ���[�g�p�����[�^1�Ԃ� �V�F�[�_���\�[�X�r���[���Z�b�g
    spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);

    // �|���S���̕`��i4���_�Ŏl�p�`�j
    commandList->DrawInstanced(4, 1, 0, 0);
}

//void PostEffect::Initialize()
//{
//    HRESULT result = S_FALSE;
//
//    SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
//
//    //���N���X�Ƃ��ď�����
//    Sprite::Initialize();
//
//    //�e�N�X�`�����\�[�X�ݒ�
//    D3D12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
//        DXGI_FORMAT_R8G8B8A8_UNORM,
//        WinApp::window_width,
//        (UINT)WinApp::window_height,
//        1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
//    );
//
//    //�e�N�X�`���o�b�t�@�̐���
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
