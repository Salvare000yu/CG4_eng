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
//	/// �R���X�g���N�^
//	/// </summary>
//	PostEffect();
//
//	/// <summary>
//	/// �`��R�}���h�̔��s
//	/// </summary>
//	/// <param name="cmdList">�R�}���h���X�g</param>
//	void Draw(ID3D12GraphicsCommandList* cmdList);
//
//	ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }
//
//private:
//	//�؂��R�}���h���X�g
//	ID3D12GraphicsCommandList* commandList_ = nullptr;
//
//	// �e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
//	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
//
//	// �p�C�v���C���Z�b�g
//	PipelineSet pipelineSet;
//};