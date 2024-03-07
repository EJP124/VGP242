#include "GameState.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Math;
using namespace KTEngine::Input;
using namespace KTEngine::Colors;

void GameState::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";

	mConstantBuffer.Initialize(sizeof(Matrix4));
	// Create a vertex buffer
	mMeshBuffer.Initialize(mMesh);

	// Create a vertex shader
	mVertexShader.Initialize<VertexPX>(shaderFile);

	// Create a pixel shader
	mPixelShader.Initialize(shaderFile);
}

void GameState::CreateShape() 
{ 
	mMesh = MeshBuilder::CreateSpherePC(30, 12, 50.0f);
}

void GameState::Terminate()
{
}

void GameState::Update(float deltaTime)
{
	UpdateCameraControl(deltaTime);
}

void GameState::Render()
{
	
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug UI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	
	ImGui::End();
}

void GameState::UpdateCameraControl(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}
