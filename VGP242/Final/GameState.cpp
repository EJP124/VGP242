#include "GameState.h"


using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Math;
using namespace KTEngine::Input;
using namespace KTEngine::Colors;

void GameState::Initialize()
{
	_drawCir = true;
	_drawPlane = true;
	_debugColor = Colors::White;
	mCamera.SetPosition({ 100.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";

	mConstantBuffer.Initialize(sizeof(Matrix4));

	// Create a vertex shader
	mVertexShader.Initialize<VertexPX>(shaderFile);

	// Create a pixel shader
	mPixelShader.Initialize(shaderFile);

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	CreateShape();
}

void GameState::CreateShape() 
{ 
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/venus.jpg", 3.0f, 55.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/saturn.jpg", 2.0f, 20.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/uranus.jpg", 1.0f, 40.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/sun.jpg", 10.0f, 0.0f));
}



void GameState::Terminate()
{
	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCameraControl(deltaTime);
	for (int i = 0; i < mPlanets.size(); i++)
	{
		mPlanets[i]->Update(deltaTime, 1.0f, 100.0f);
	}
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);

	for (int i = 0; i < mPlanets.size(); i++)
	{
		mPlanets[i]->Render(mCamera, mConstantBuffer);
		if (_drawCir)
		{
			SimpleDraw::AddGroundCircle(40, mPlanets[i]->GetDistance(), _debugColor);
		}
	}
	

	SimpleDraw::Render(mCamera);
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug UI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Draw Route", &_drawCir);
	ImGui::Checkbox("Draw Plane", &_drawPlane);
	ImGui::ColorEdit4("RouteCOlor##", &_debugColor.r);
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
