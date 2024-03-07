#pragma once
#include <KTEngine/Inc/KTEngine.h>

using namespace KTEngine;
using namespace KTEngine::Graphics;

class GameState : public KTEngine::AppState
{
public:
	enum class ShapeType
	{
		Transform,
		Sphere,
		AABB,
		AABBFilled,
		Custom,
		Count
	};
	virtual ~GameState() = default;

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	void UpdateCameraControl(float deltaTime);

	Camera mCamera;
	ShapeType mShapeType = ShapeType::Transform;
	float mSphereRadius = 1.0f;
	bool draw = true;
	Vector3 min = {-1, -1, -1};
	Vector3 max = { 1, 1, 1 };
	Color mShapeColor = Colors::BlueViolet;
};