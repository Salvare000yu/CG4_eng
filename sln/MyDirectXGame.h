#pragma once

#include "GameBass.h"

#include "FbxLoader.h"

#include <vector>
/// <summary>
/// ゲーム固有クラス
/// </summary>
class MyDirectXGame:public GameBass
{
public:

    void Initialize() override;

    void Finalize() override;

    /// <summary>
    /// 毎フレーム更新
    /// </summary>
    void Update() override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

private:

    std::vector<Sprite*> sprites;

    Model* model_1 = nullptr;
    Model* model_2 = nullptr;

    Object3d* object3d_1 = nullptr;
    Object3d* object3d_2 = nullptr;
    Object3d* object3d_3 = nullptr;
};

