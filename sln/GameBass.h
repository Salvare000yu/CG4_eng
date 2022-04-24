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
    /// ���s
    /// </summary>
    void Run();

    /// <summary>
/// ������
/// </summary>
    virtual void Initialize();

    /// <summary>
/// �I��
/// </summary>
    virtual void Finalize();

    /// <summary>
    /// ���t���[���X�V
    /// </summary>
    virtual void Update();

    /// <summary>
/// �`��
/// </summary>
    virtual void Draw()=0;

    virtual bool IsEndReq() { return endReq_; }
protected:
    bool endReq_ = false;
    //�|�C���^�n����
    Input* input = nullptr;
    WinApp* winApp = nullptr;
    DirectXCommon* dxCommon = nullptr;
    Audio* audio = nullptr;
    DebugText* debugText = nullptr;
    SpriteCommon* spriteCommon = nullptr;
};

