#pragma once

#include "GameBass.h"

#include "FbxLoader.h"

#include <vector>
/// <summary>
/// �Q�[���ŗL�N���X
/// </summary>
class MyDirectXGame:public GameBass
{
public:

    void Initialize() override;

    void Finalize() override;

    /// <summary>
    /// ���t���[���X�V
    /// </summary>
    void Update() override;
    /// <summary>
    /// �`��
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

