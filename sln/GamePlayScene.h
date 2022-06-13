#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"

#include "Camera.h"

#include "FbxObject3d.h"

#include <memory>

class GamePlayScene :public BaseScene
{
public:

	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;
	void DrawUI() override;

	std::unique_ptr<Camera> camera; //�J����

private:

	std::unique_ptr < Sprite> sprite_back = nullptr;

	std::unique_ptr < Model> model_1 = nullptr;
	std::unique_ptr < Model> model_2 = nullptr;
	std::unique_ptr < Model> model_3 = nullptr;
	std::unique_ptr < Model> model_ban = nullptr;

	std::unique_ptr < Object3d> object3d_1 = nullptr;
	std::unique_ptr < Object3d> object3d_2 = nullptr;
	std::unique_ptr < Object3d> object3d_3 = nullptr;
	std::unique_ptr < Object3d> object3d_ban = nullptr;

	FbxModel* fbxModel_1 = nullptr;
	FbxObject3d* fbxObject_1=nullptr;
};

