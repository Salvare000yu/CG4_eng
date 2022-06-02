#include "GamePlayScene.h"
#include "SceneManager.h"
#include "GameSound.h"
#include "Input.h"
#include "DebugText.h"
#include "FbxLoader.h"
#include "DirectXCommon.h"
#include "EndScene.h"
#include "FbxObject3d.h"

#include "safe_delete.h"

#include <DirectXMath.h>
using namespace DirectX;

void GamePlayScene::Initialize()
{
#pragma region 描画初期化処理

	camera.reset(new Camera(WinApp::window_width, WinApp::window_height));

	camera->SetTarget({ 0,5,0 });
	camera->SetEye({ 0,5,-10 });

	//デバイスをセット
	FbxObject3d::SetDevice(DirectXCommon::GetInstance()->GetDevice());
	// カメラセット
	Object3d::SetCamera(camera.get());
	//グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
	FbxObject3d::SetCamera(camera.get());

	//---objからモデルデータ読み込み---
	model_1.reset(Model::LoadFromOBJ("ground"));
	model_2.reset(Model::LoadFromOBJ("triangle_mat"));
	//Model* model_3 = Model::LoadFromOBJ("chr_sword");
	//------3dオブジェクト生成------//
	object3d_1.reset(Object3d::Create());
	object3d_2.reset(Object3d::Create());
	object3d_3.reset(Object3d::Create());
	//------3dオブジェクトに3dモデルを紐づける------//
	object3d_1->SetModel(model_1.get());
	object3d_2->SetModel(model_2.get());
	object3d_3->SetModel(model_2.get());

	//------object3dスケール------//
	object3d_1->SetScale({ 100.0f, 20.0f, 500.0f });
	object3d_2->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_3->SetScale({ 10.0f, 10.0f, 10.0f });

	//------object3d位置------//
	object3d_1->SetPosition({ 0,-1,0 });
	object3d_2->SetPosition({ 5,-1,5 });
	object3d_3->SetPosition({ 0,-1,5 });

	fbxModel_1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//----------FBX オブジェクト生成とモデルのセット-----------//
	fbxObject_1 = new FbxObject3d;

	fbxObject_1->Initialize();

	//------fbxセット------//
	fbxObject_1->SetModel(fbxModel_1);

	//------fbxスケール------//
	fbxObject_1->SetScale({ 0.05f, 0.05f, 0.05f });

	//------fbx位置------//
	fbxObject_1->SetPosition({ 0,0,100 });

	// 音声読み込み
	GameSound::GetInstance()->LoadWave("E_rhythmaze_128.wav");
	GameSound::GetInstance()->LoadWave("theworld_audio_avisyuturyoku.wav");
	GameSound::GetInstance()->LoadWave("muda_diego.wav");
	GameSound::GetInstance()->LoadWave("oredakenojikan.wav");
	// 音声再生 鳴らしたいとき
	GameSound::GetInstance()->PlayWave("E_rhythmaze_128.wav");
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
	//FbxLoader::GetInstance()->LoadModelFromFile(
	//	"cube"
	//);

#pragma endregion 描画初期化処理

	int counter = 0; // アニメーションの経過時間カウンター
}

void GamePlayScene::Finalize()
{
	safe_delete(fbxObject_1);
	safe_delete(fbxModel_1);
}

void GamePlayScene::Update()
{
	//トリガーキー使う
	bool TriggerKey(UINT index);

	Input* input = Input::GetInstance();

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
	const bool inputQ = input->PushKey(DIK_Q);
	const bool inputZ = input->PushKey(DIK_Z);
	const bool inputT = input->PushKey(DIK_T);

	const bool TriggerJ = input->TriggerKey(DIK_J);
	const bool TriggerM = input->TriggerKey(DIK_M);
	const bool TriggerK = input->TriggerKey(DIK_K);
	const bool TriggerE = input->TriggerKey(DIK_E);

	if (inputW || inputS || inputA || inputD || inputQ || inputZ)
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
		if (inputQ) {
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

	if (TriggerJ)
	{
		//Jで音鳴らす
		GameSound::GetInstance()->PlayWave("theworld_audio_avisyuturyoku.wav");
	}
	if (TriggerM)
	{
		//Mで音鳴らす
		GameSound::GetInstance()->PlayWave("muda_diego.wav");
	}
	if (TriggerK)
	{
		//Kで音鳴らす
		GameSound::GetInstance()->PlayWave("oredakenojikan.wav");
	}

	if (inputT) // Tキーが押されていたら
	{
		OutputDebugStringA("Hit !(^^)!\n");  // 出力ウィンドウに「Hit 0」と表示

		//T押してる時表示
		DebugText::GetInstance()->Print("Look at output window![Thank you for watching... !(^^)!]", 200, 50,1.5);
	}

	if (TriggerE)     // スペースキーが押されていたら
	{
		//シーン切り替え
		BaseScene* scene = new EndScene();
		sceneManager_->SetNextScene(scene);
	}

	DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	DebugText::GetInstance()->Print("[WASD:front,back,right,left] [ZE:up,down] [T:outputwindow]", 200, 150, 1.0f);
	DebugText::GetInstance()->Print("JMK:sound", 200, 200, 1.0f);

	camera->Update();

	//3dobj
	object3d_1->Update();
	object3d_2->Update();
	object3d_3->Update();

	// FBX Update
	fbxObject_1->Update();

	//スプライト更新
	sprite->Update();
}

void GamePlayScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();

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

	// FBX3dオブジェクト描画
	fbxObject_1->Draw(cmdList);

	//パーティクル描画
	//particleMan->Draw(cmdList);

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