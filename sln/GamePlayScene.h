#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"

#include "Camera.h"

class GamePlayScene:public BaseScene
{
public:

    void Initialize() override;

    void Finalize() override;

    void Update() override;

    void Draw() override;
    void DrawUI() override;

    Camera* camera = nullptr; //ÉJÉÅÉâ

private:

    Sprite* sprite = nullptr;

    Model* model_1 = nullptr;
    Model* model_2 = nullptr;

    Object3d* object3d_1 = nullptr;
    Object3d* object3d_2 = nullptr;
    Object3d* object3d_3 = nullptr;
};

