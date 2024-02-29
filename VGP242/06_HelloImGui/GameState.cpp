#include "GameState.h"


using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Math;
using namespace KTEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
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
	switch (mShapeType)
	{
	case ShapeType::Transform:
		SimpleDraw::AddTransform(Matrix4::Identity);
		break;
	case ShapeType::Sphere:
		SimpleDraw::AddSphere(30, 30, mSphereRadius, mShapeColor);
		break;
	case ShapeType::AABB:
		SimpleDraw::AddAABB({-1, -1, -1}, {1, 1, 1}, mShapeColor);
		break;
	case ShapeType::AABBFilled:
		SimpleDraw::AddFilledAABB({ -1, -1, -1 }, { 1, 1, 1 }, mShapeColor);
		break;
	case ShapeType::Custom:
		SimpleDraw::AddFilledAABB({ -1, -1, -1 }, { 1, 1, 1 }, mShapeColor);
		break;
	default:
		break;
	}

	SimpleDraw::Render(mCamera);
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
