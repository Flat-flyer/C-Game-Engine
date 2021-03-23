#include "GameScene.h"

GameScene::GameScene():shape(nullptr)
{
}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	std::cout << "Game scene" << std::endl;
	Debug::Info("Game Scene Started", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.9f, glm::vec3(1.0f, 0.0f, 1.0f)));

	model = new Model("Resources/Models/Apple.obj", "Resources/Models/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	//model->SetScale(glm::vec3(0.5f));

	shape = new GameObject(model);
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	shape->Update(deltaTime_);

}

void GameScene::Render()
{
	shape->Render(CoreEngine::GetInstance()->GetCamera());
}
