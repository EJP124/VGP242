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
protected:
	virtual void CreateShape();
private:
	void UpdateCameraControl(float deltaTime);
	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexShader;
	PixelShader mPixelShader;

	MeshPC mMesh;

	Texture mTexture;
	Sampler mSampler;
	
};