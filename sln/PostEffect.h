#pragma once
#include "Sprite.h"
#include "SpriteBase.h"
#include "PipelineSet.h"

// Microsoft::WRL::���ȗ�
template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
// DirectX::���ȗ�
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
	/// �`��R�}���h�̔��s
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void Draw();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

private:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PostEffect();

public:
	//ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }



	//�V�[���`��O����
	void PreDrawScene(ID3D12GraphicsCommandList* commandList);
	//�V�[���`��㏈��
	void PostDrawScene(ID3D12GraphicsCommandList* commandList);

	static void SetDevice(ID3D12Device* device);

	//��ʃN���A�J���[
	static const float clearColor[4];

private:

	static ID3D12Device* device_;

	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff_;
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource>depthBuff;
	//RTV�p�f�X�N���v�^�e�[�u��
	ComPtr<ID3D12DescriptorHeap>descHeapRTV;
	//DSV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap>descHeapDSV;

	//�؂��R�}���h���X�g
	//ID3D12GraphicsCommandList* commandList_ = nullptr;

	// �e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
	//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;

	// �p�C�v���C���Z�b�g
	//PipelineSet pipelineSet;
};