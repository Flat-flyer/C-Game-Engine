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

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(3);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	v.colour = glm::vec3(0.5f, 0.5f, 0.5f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);

	Model* model = new Model(ShaderHandler::GetInstance()->GetShader("colourShader"));
	model->AddMesh(new Mesh(vertexList));
	vertexList.clear();

	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	model->AddMesh(new Mesh(vertexList));

	shape = new GameObject(model);
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	std::cout << deltaTime_ << std::endl;
}

void GameScene::Render()
{
	shape->Render();
}
