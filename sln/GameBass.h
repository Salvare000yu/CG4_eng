#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Audio.h"

class GameBass
{
public:

    /// <summary>
    /// 実行
    /// </summary>
    void Run();

    /// <summary>
/// 初期化
/// </summary>
    virtual void Initialize();

    /// <summary>
/// 終了
/// </summary>
    virtual void Finalize();

    /// <summary>
    /// 毎フレーム更新
    /// </summary>
    virtual void Update();

    /// <summary>
/// 描画
/// </summary>
    virtual void Draw()=0;

    virtual bool IsEndReq() { return endReq_; }
protected:
    bool endReq_ = false;
    //ポインタ系ここ
    Input* input = nullptr;
    WinApp* winApp = nullptr;
    DirectXCommon* dxCommon = nullptr;
    Audio* audio = nullptr;
    DebugText* debugText = nullptr;
    SpriteCommon* spriteCommon = nullptr;
};

