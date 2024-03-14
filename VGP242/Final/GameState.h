#pragma once
#include <KTEngine/Inc/KTEngine.h>
#include "Planet.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

class GameState : public KTEngine::AppState
{
public:
	virtual ~GameState() = default;

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
protected:
	virtual void CreateShape();
private:
	void UpdateCameraControl(float deltaTime);
	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	VertexShader mVertexShader;
	PixelShader mPixelShader;
	Sampler mSampler;

	bool _drawCir;
	bool _drawPlane;
	Color _debugColor;

	std::vector<std::shared_ptr<Planet>> mPlanets;
	
};