#include <Infrastructure/GameModule.hpp>

#include <RenderingEngine\RenderingEngine.hpp>
#include <RenderingEngine\Mesh\ObjLoader.hpp>
#include <RenderingEngine\Mesh\Mesh.hpp>
#include <RenderingEngine\Renderables\Model.hpp>
#include <RenderingEngine\Image\Image.hpp>

#include <Infrastructure\LabyrinthGenerator.hpp>

static std::vector<RenderingEngine::Vertex> objFile;
static RenderingEngine::Mesh mesh;
static RenderingEngine::Image* image;
static RenderingEngine::OpenGL::Texture* texture;

static std::vector<RenderingEngine::Model*> models;

static void AddWall(glm::vec2 position)
{
	RenderingEngine::Model* model = new RenderingEngine::Model;
	model->UploadMesh(mesh);

	model->SetPosition({position.x, position.y, 0.0f});
	model->SetScale({ 1.0f, 0.5f, 1.0f });

	model->options.Textures["tex"] = texture;
	RenderingEngine::Context::GetInstance()->AddRenderable(model);

	models.push_back(model);
}

static void AddLabyrinth()
{
	LabyrinthGenerator generator(25, 25);

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (generator.IsWalled(i, j))
			{
				AddWall({i, j});
			}
		}
	}
}

static void OnGameStart()
{
	objFile = RenderingEngine::LoadOBJ("../Assets/obj/Wall/Wall.obj");
	mesh.UploadOBJ(objFile);

	image = new RenderingEngine::Image("../Assets/textures/brick-wall.jpg");

	texture = new RenderingEngine::OpenGL::Texture;

	texture->Image2D(image->GetPixels(),
		RenderingEngine::OpenGL::DataType::UnsignedByte,
		RenderingEngine::OpenGL::Format::RGBA,
		image->GetWidth(),
		image->GetHeight(),
		RenderingEngine::OpenGL::InternalFormat::RGBA);

	texture->SetWrappingR(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	texture->SetWrappingS(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	texture->SetWrappingT(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	texture->SetFilters(RenderingEngine::OpenGL::Filter::LinearMipmapNearest, RenderingEngine::OpenGL::Filter::NearestMipmapLinear);
	texture->GenerateMipmaps();

	AddLabyrinth();
}

static void OnGameEnd()
{
	for (auto& model : models)
	{
		delete model;
	}
	
	delete texture;
	delete image;
}

bool ModuleInit()
{
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameStartCallback(OnGameStart);
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameEndCallback(OnGameStart);
	return true;
}
