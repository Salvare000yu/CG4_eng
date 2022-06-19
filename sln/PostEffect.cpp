//#include "PostEffect.h"
//#include <d3dx12.h>
//
//using namespace DirectX;
//
//PostEffect::PostEffect()
//    : Sprite(
//        100,					//�e�N�X�`���ԍ�
//        { 0, 0 ,0},					//���W
//        { 500.0f, 500.0f },		//�T�C�Y
//        { 1, 1, 1, 1 },			//�F
//        { 0.0f, 0.0f },			//�A���J�[�|�C���g
//        false,					//���E���]�t���O
//        false)					//�㉺���]�t���O
//{
//}
//
//void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
//{
//    if (isInvisible) {
//        return;
//    }
//
//    SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
//
//    ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();
//
//
//
//    commandList_ = commandList;
//    // �p�C�v���C���X�e�[�g�̐ݒ�
//    commandList_->SetPipelineState(pipelineSet.pipelinestate.Get());
//    // ���[�g�V�O�l�`���̐ݒ�
//    commandList_->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
//    // �v���~�e�B�u�`���ݒ�
//    commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//    // �e�N�X�`���p�f�X�N���v�^�q�[�v�̐ݒ�
//    ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
//    commandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
//
//
//
//    // ���_�o�b�t�@���Z�b�g
//    commandList->IASetVertexBuffers(0, 1, &vbView_);
//
//    // ���[�g�p�����[�^0�Ԃɒ萔�o�b�t�@���Z�b�g
//    commandList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());
//
//    // ���[�g�p�����[�^1�Ԃ� �V�F�[�_���\�[�X�r���[���Z�b�g
//    spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);
//
//    // �|���S���̕`��i4���_�Ŏl�p�`�j
//    commandList->DrawInstanced(4, 1, 0, 0);
//}