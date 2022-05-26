#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"

#include "Camera.h"

#include <memory>

class GamePlayScene :public BaseScene
{
public:

	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;
	void DrawUI() override;

	std::unique_ptr<Camera> camera; //ÉJÉÅÉâ

private:

	std::unique_ptr < Sprite> sprite = nullptr;

	std::unique_ptr < Model> model_1 = nullptr;
	std::unique_ptr < Model> model_2 = nullptr;

	std::unique_ptr < Object3d> object3d_1 = nullptr;
	std::unique_ptr < Object3d> object3d_2 = nullptr;
	std::unique_ptr < Object3d> object3d_3 = nullptr;
};

