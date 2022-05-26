#include "GamePlayScene.h"
#include "SceneManager.h"
#include "GameSound.h"
#include "Input.h"
#include "DebugText.h"
#include "FbxLoader.h"
#include "DirectXCommon.h"

#include <DirectXMath.h>
using namespace DirectX;

void GamePlayScene::Initialize()
{
#pragma region �`�揉��������

	camera.reset(new Camera(WinApp::window_width, WinApp::window_height));

	camera->SetTarget({ 0,5,0 });
	camera->SetEye({ 0,5,-10 });

	// �J�����Z�b�g
	Object3d::SetCamera(camera.get());

	//---obj���烂�f���f�[�^�ǂݍ���---
	model_1.reset(Model::LoadFromOBJ("ground"));
	model_2.reset(Model::LoadFromOBJ("triangle_mat"));
	//Model* model_3 = Model::LoadFromOBJ("chr_sword");
	//---3d�I�u�W�F�N�g����---
	object3d_1.reset(Object3d::Create());
	object3d_2.reset(Object3d::Create());
	object3d_3.reset(Object3d::Create());
	//---3d�I�u�W�F�N�g��3d���f����R�Â���---
	object3d_1->SetModel(model_1.get());
	object3d_2->SetModel(model_2.get());
	object3d_3->SetModel(model_2.get());

	object3d_1->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_2->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_3->SetScale({ 10.0f, 10.0f, 10.0f });

	object3d_1->SetPosition({ 0,-1,5 });
	object3d_2->SetPosition({ 5,-1,5 });
	object3d_3->SetPosition({ 0,-1,5 });

	// �����ǂݍ���
	GameSound::GetInstance()->LoadWave("A_rhythmaze_125.wav");
	GameSound::GetInstance()->LoadWave("theworld_audio_avisyuturyoku.wav");
	// �����Đ� �炵�����Ƃ�
	GameSound::GetInstance()->PlayWave("A_rhythmaze_125.wav");
	GameSound::GetInstance()->PlayWave("theworld_audio_avisyuturyoku.wav");
	// 3D�I�u�W�F�N�g�̐�
	//const int OBJECT_NUM = 2;

	//Object3d object3ds[OBJECT_NUM];

	// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/play.png");

	// �X�v���C�g�̐���
	sprite.reset(Sprite::Create(1, { 0,0 }, false, false));
	//for (int i = 0; i < 1; i++)
	//{
	//    int texNumber = 1;
	//    Sprite* sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

	//    // �X�v���C�g�̍��W�ύX
	//    sprite->SetPosition({ (float)(80),(float)(20),0 });
	//    //sprite->SetRotation((float)(rand() % 360));
	//    sprite->SetSize({ (float)(200), (float)(200) });

	//    sprite->TransferVertexBuffer();

	//    sprites.push_back(sprite);
	//}

	//fbx ���f�����w�肵�ăt�@�C���ǂݍ���
	FbxLoader::GetInstance()->LoadModelFromFile(
		"cube"
	);

#pragma endregion �`�揉��������

	int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[
}

void GamePlayScene::Finalize()
{

}

void GamePlayScene::Update()
{
	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_0)) // ������0�L�[��������Ă�����
	{
		OutputDebugStringA("Hit 0\n");  // �o�̓E�B���h�E�ɁuHit 0�v�ƕ\��
	}

	float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

	if (input->PushKey(DIK_SPACE))     // �X�y�[�X�L�[��������Ă�����
	{
		// ��ʃN���A�J���[�̐��l������������
		clearColor[1] = 1.0f;
	}

	// ���W����
	const bool inputUp = input->PushKey(DIK_UP);
	const bool inputDown = input->PushKey(DIK_DOWN);
	const bool inputRight = input->PushKey(DIK_RIGHT);
	const bool inputLeft = input->PushKey(DIK_LEFT);

	// ���W����
	if (inputUp || inputDown || inputRight || inputLeft)
	{

	}

	const bool inputW = input->PushKey(DIK_W);
	const bool inputS = input->PushKey(DIK_S);
	const bool inputA = input->PushKey(DIK_A);
	const bool inputD = input->PushKey(DIK_D);
	const bool inputE = input->PushKey(DIK_E);
	const bool inputZ = input->PushKey(DIK_Z);
	if (inputW || inputS || inputA || inputD || inputE || inputZ)
	{
		constexpr float moveSpeed = 1;
		if (inputS) {
			// �J�������o�b�N������
			camera->MoveEyeVector(XMFLOAT3(0, 0, -moveSpeed));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x, camera->GetTarget().y, camera->GetTarget().z - moveSpeed));
		}
		if (inputW) {
			// �J������O�i������
			camera->MoveEyeVector(XMFLOAT3(0, 0, +moveSpeed));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x, camera->GetTarget().y, camera->GetTarget().z + moveSpeed));
		}
		if (inputA) {
			// �J���������i������
			camera->MoveEyeVector(XMFLOAT3(-moveSpeed, 0, 0));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x - moveSpeed, camera->GetTarget().y, camera->GetTarget().z));
		}
		if (inputD) {
			// �J�������E�i������
			camera->MoveEyeVector(XMFLOAT3(moveSpeed, 0, 0));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x + moveSpeed, camera->GetTarget().y, camera->GetTarget().z));
		}
		if (inputE) {
			// �J�������㏸������
			camera->MoveEyeVector(XMFLOAT3(0, moveSpeed, 0));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x, camera->GetTarget().y + moveSpeed, camera->GetTarget().z));
		}
		if (inputZ) {
			// �J���������~������
			camera->MoveEyeVector(XMFLOAT3(0, -moveSpeed, 0));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x, camera->GetTarget().y - moveSpeed, camera->GetTarget().z));
		}
	}

	DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	DebugText::GetInstance()->Print("WASD:front,back,right,left ZE:up,down", 200, 200, 2.0f);

	camera->Update();

	//3dobj
	object3d_1->Update();
	object3d_2->Update();
	object3d_3->Update();

	//�X�v���C�g�X�V
	sprite->Update();
}

void GamePlayScene::Draw()
{
	//// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDraw();
	//SpriteCommonBeginDraw(spriteCommon, dxCommon->GetCmdList());
	//// �X�v���C�g�`��
	sprite->Draw();

	//3d�I�u�W�F�`��O����
	Object3d::PreDraw(DirectXCommon::GetInstance()->GetCmdList());

	//3d�I�u�W�F�`��
	object3d_1->Draw();
	object3d_2->Draw();
	object3d_3->Draw();

	//3d�I�u�W�F�`��㏈��
	Object3d::PostDraw();

	// �S�D�`��R�}���h��������

	//for (int i = 0; i < _countof(object3ds); i++)
	//{
	//    DrawObject3d(&object3ds[i], dxCommon->GetCmdList(), basicDescHeap.Get(), vbView, ibView,
	//        CD3DX12_GPU_DESCRIPTOR_HANDLE(basicDescHeap->GetGPUDescriptorHandleForHeapStart(), constantBufferNum, dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)),
	//        indices, _countof(indices));
	//}

	//// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDraw();
	//SpriteCommonBeginDraw(spriteCommon, dxCommon->GetCmdList());
	//// �X�v���C�g�`��
   // sprite->Draw();
}

void GamePlayScene::DrawUI()
{
}
