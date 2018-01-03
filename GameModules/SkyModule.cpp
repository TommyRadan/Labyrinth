#include <Infrastructure/GameModule.hpp>

#include <RenderingEngine\RenderingEngine.hpp>
#include <RenderingEngine\Mesh\ObjLoader.hpp>
#include <RenderingEngine\Mesh\Mesh.hpp>
#include <RenderingEngine\Renderables\Model.hpp>

std::vector<RenderingEngine::Vertex> objFile;
RenderingEngine::Mesh mesh;
RenderingEngine::Model* model;

static void OnGameStart()
{
	objFile = RenderingEngine::LoadOBJ("Assets/SkyBox.obj");
	mesh.UploadOBJ(objFile);

	model = new RenderingEngine::Model;
	model->UploadMesh(mesh);

	RenderingEngine::Context::GetInstance()->AddRenderable(model);
}

static void OnGameEnd()
{
	delete model;
}

bool ModuleInit()
{
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameStartCallback(OnGameStart);
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameEndCallback(OnGameEnd);
	return true;
}
