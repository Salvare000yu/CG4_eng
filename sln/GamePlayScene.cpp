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
#pragma region 描画初期化処理

	camera.reset(new Camera(WinApp::window_width, WinApp::window_height));

	camera->SetTarget({ 0,5,0 });
	camera->SetEye({ 0,5,-10 });

	// カメラセット
	Object3d::SetCamera(camera.get());

	//---objからモデルデータ読み込み---
	model_1.reset(Model::LoadFromOBJ("ground"));
	model_2.reset(Model::LoadFromOBJ("triangle_mat"));
	//Model* model_3 = Model::LoadFromOBJ("chr_sword");
	//---3dオブジェクト生成---
	object3d_1.reset(Object3d::Create());
	object3d_2.reset(Object3d::Create());
	object3d_3.reset(Object3d::Create());
	//---3dオブジェクトに3dモデルを紐づける---
	object3d_1->SetModel(model_1.get());
	object3d_2->SetModel(model_2.get());
	object3d_3->SetModel(model_2.get());

	object3d_1->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_2->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_3->SetScale({ 10.0f, 10.0f, 10.0f });

	object3d_1->SetPosition({ 0,-1,5 });
	object3d_2->SetPosition({ 5,-1,5 });
	object3d_3->SetPosition({ 0,-1,5 });

	// 音声読み込み
	GameSound::GetInstance()->LoadWave("A_rhythmaze_125.wav");
	GameSound::GetInstance()->LoadWave("theworld_audio_avisyuturyoku.wav");
	// 音声再生 鳴らしたいとき
	GameSound::GetInstance()->PlayWave("A_rhythmaze_125.wav");
	GameSound::GetInstance()->PlayWave("theworld_audio_avisyuturyoku.wav");
	// 3Dオブジェクトの数
	//const int OBJECT_NUM = 2;

	//Object3d object3ds[OBJECT_NUM];

	// スプライト共通テクスチャ読み込み
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/play.png");

	// スプライトの生成
	sprite.reset(Sprite::Create(1, { 0,0 }, false, false));
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

	//fbx モデル名指定してファイル読み込み
	FbxLoader::GetInstance()->LoadModelFromFile(
		"cube"
	);

#pragma endregion 描画初期化処理

	int counter = 0; // アニメーションの経過時間カウンター
}

void GamePlayScene::Finalize()
{

}

void GamePlayScene::Update()
{
	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
	{
		OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
	}

	float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

	if (input->PushKey(DIK_SPACE))     // スペースキーが押されていたら
	{
		// 画面クリアカラーの数値を書き換える
		clearColor[1] = 1.0f;
	}

	// 座標操作
	const bool inputUp = input->PushKey(DIK_UP);
	const bool inputDown = input->PushKey(DIK_DOWN);
	const bool inputRight = input->PushKey(DIK_RIGHT);
	const bool inputLeft = input->PushKey(DIK_LEFT);

	// 座標操作
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
			// カメラをバックさせる
			camera->MoveEyeVector(XMFLOAT3(0, 0, -moveSpeed));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x, camera->GetTarget().y, camera->GetTarget().z - moveSpeed));
		}
		if (inputW) {
			// カメラを前進させる
			camera->MoveEyeVector(XMFLOAT3(0, 0, +moveSpeed));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x, camera->GetTarget().y, camera->GetTarget().z + moveSpeed));
		}
		if (inputA) {
			// カメラを左進させる
			camera->MoveEyeVector(XMFLOAT3(-moveSpeed, 0, 0));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x - moveSpeed, camera->GetTarget().y, camera->GetTarget().z));
		}
		if (inputD) {
			// カメラを右進させる
			camera->MoveEyeVector(XMFLOAT3(moveSpeed, 0, 0));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x + moveSpeed, camera->GetTarget().y, camera->GetTarget().z));
		}
		if (inputE) {
			// カメラを上昇させる
			camera->MoveEyeVector(XMFLOAT3(0, moveSpeed, 0));
			camera->SetTarget(XMFLOAT3(camera->GetTarget().x, camera->GetTarget().y + moveSpeed, camera->GetTarget().z));
		}
		if (inputZ) {
			// カメラを下降させる
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

	//スプライト更新
	sprite->Update();
}

void GamePlayScene::Draw()
{
	//// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDraw();
	//SpriteCommonBeginDraw(spriteCommon, dxCommon->GetCmdList());
	//// スプライト描画
	sprite->Draw();

	//3dオブジェ描画前処理
	Object3d::PreDraw(DirectXCommon::GetInstance()->GetCmdList());

	//3dオブジェ描画
	object3d_1->Draw();
	object3d_2->Draw();
	object3d_3->Draw();

	//3dオブジェ描画後処理
	Object3d::PostDraw();

	// ４．描画コマンドここから

	//for (int i = 0; i < _countof(object3ds); i++)
	//{
	//    DrawObject3d(&object3ds[i], dxCommon->GetCmdList(), basicDescHeap.Get(), vbView, ibView,
	//        CD3DX12_GPU_DESCRIPTOR_HANDLE(basicDescHeap->GetGPUDescriptorHandleForHeapStart(), constantBufferNum, dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)),
	//        indices, _countof(indices));
	//}

	//// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDraw();
	//SpriteCommonBeginDraw(spriteCommon, dxCommon->GetCmdList());
	//// スプライト描画
   // sprite->Draw();
}

void GamePlayScene::DrawUI()
{
}
