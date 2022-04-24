#include "GameBass.h"

void GameBass::Run()
{
    Initialize();

    while (true)  // ゲームループ
    {
        //毎フレーム処理
        Update();

        //終了リクエストで抜ける
        if (endReq_)
        {
            break;
        }
        //描画
        Draw();

    }
    //終了
    Finalize();
}

void GameBass::Initialize()
{

    // FbxManager* fbxManager = FbxManager::Create();
     //windowsAPI初期化
    winApp = new WinApp();
    winApp->Initialize();

    MSG msg{};  // メッセージ

#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理
    // DirectX初期化処理　ここから
   // HRESULT result;
    //DirectXの初期化
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);

    // スプライト共通部分初期化
    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);

    //const int SPRITES_NUM = 1;
    //Sprite sprites[SPRITES_NUM];

      // デバッグテキスト
    debugText = new DebugText();

    // デバッグテキスト用のテクスチャ番号を指定
    const int debugTextTexNumber = 0;
    // デバッグテキスト用のテクスチャ読み込み
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    debugText->Initialize(spriteCommon, debugTextTexNumber);

    //入力の初期化
    input = new Input();
    input->Initialize(winApp);

    //オーディオの初期化
    audio = new Audio();
    audio->Initialize();

    //3dオブジェクト静的初期化
    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
}

void GameBass::Finalize()
{
    //デバッグテキスト解放
    debugText->Finalize();
    delete debugText;

    //sprite共通解放
    delete spriteCommon;

    //オーディオ解放
    audio->Finalize();
    delete audio;

    //DirectX解放
    delete dxCommon;
    //入力解放
    delete input;

    //windowsAPIの終了処理
    winApp->Finalize();

    //windowsAPI解放
    delete winApp;
}

void GameBass::Update()
{
#pragma region ウィンドウメッセージ処理
    //// メッセージがある？
    //if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    //    TranslateMessage(&msg); // キー入力メッセージの処理
    //    DispatchMessage(&msg); // プロシージャにメッセージを送る
    //}

    //// ✖ボタンで終了メッセージが来たらゲームループを抜ける
    //if (msg.message == WM_QUIT) {
    //    break;
    //}
        //windowsのメッセージ処理
    if (winApp->ProcessMessage()) {
        //ゲームループ抜ける
        endReq_ = true;
        return;
    }
#pragma endregion ウィンドウメッセージ処理
    //入力更新
    input->Update();
}

void GameBass::Draw()
{
}
