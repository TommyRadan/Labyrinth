#include <Infrastructure/GameModule.hpp>

#include <RenderingEngine\RenderingEngine.hpp>
#include <RenderingEngine\Mesh\ObjLoader.hpp>
#include <RenderingEngine\Mesh\Mesh.hpp>
#include <RenderingEngine\Renderables\Model.hpp>
#include <RenderingEngine\Image\Image.hpp>

#include <Infrastructure\LabyrinthGenerator.hpp>
#include <RenderingEngine\Camera.hpp>
#include <RenderingEngine\Window.hpp>

static std::vector<RenderingEngine::Vertex> wallObjFile;
static RenderingEngine::Mesh wallMesh;
static RenderingEngine::Image* wallImage;
static RenderingEngine::OpenGL::Texture* wallTexture;
static std::vector<RenderingEngine::Model*> wallModels;

static std::vector<RenderingEngine::Vertex> gobletObjFile;
static RenderingEngine::Mesh gobletMesh;
static RenderingEngine::Image* gobletImage;
static RenderingEngine::OpenGL::Texture* gobletTexture;
static RenderingEngine::Model* gobletModel;

static glm::vec3 gobletLocation;

#ifdef _DEBUG
#define GOBLET_OBJ "../Assets/obj/Goblet/Gablet.obj"
#define GOLD_JPG "../Assets/textures/gold.jpg"
#define WALL_OBJ "../Assets/obj/Wall/Wall.obj"
#define BRICK_WALL_JPG "../Assets/textures/brick-wall.jpg"
#else
#define GOBLET_OBJ "Assets/obj/Goblet/Gablet.obj"
#define GOLD_JPG "Assets/textures/gold.jpg"
#define WALL_OBJ "Assets/obj/Wall/Wall.obj"
#define BRICK_WALL_JPG "Assets/textures/brick-wall.jpg"
#endif

static void AddWall(glm::vec2 position)
{
	RenderingEngine::Model* model = new RenderingEngine::Model;
	model->UploadMesh(wallMesh);

	model->SetPosition({position.x, position.y, 0.0f});

	model->options.Textures["tex"] = wallTexture;
	RenderingEngine::Context::GetInstance()->AddRenderable(model);

	wallModels.push_back(model);
}

static void AddGoblet(glm::vec2 position)
{
	gobletLocation = glm::vec3(position, 0.0f);

	gobletObjFile = RenderingEngine::LoadOBJ(GOBLET_OBJ);
	gobletMesh.UploadOBJ(gobletObjFile);

	gobletImage = new RenderingEngine::Image(GOLD_JPG);

	gobletTexture = new RenderingEngine::OpenGL::Texture;

	gobletTexture->Image2D(gobletImage->GetPixels(),
		RenderingEngine::OpenGL::DataType::UnsignedByte,
		RenderingEngine::OpenGL::Format::RGBA,
		gobletImage->GetWidth(),
		gobletImage->GetHeight(),
		RenderingEngine::OpenGL::InternalFormat::RGBA);

	gobletTexture->SetWrappingR(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	gobletTexture->SetWrappingS(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	gobletTexture->SetWrappingT(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	gobletTexture->SetFilters(RenderingEngine::OpenGL::Filter::LinearMipmapNearest, RenderingEngine::OpenGL::Filter::NearestMipmapLinear);
	gobletTexture->GenerateMipmaps();

	gobletModel = new RenderingEngine::Model;
	gobletModel->UploadMesh(gobletMesh);

	gobletModel->SetPosition({ position.x, position.y, 0.0f });
	gobletModel->SetScale({0.5f, 0.5f, 0.5f});

	gobletModel->options.Textures["tex"] = gobletTexture;
	RenderingEngine::Context::GetInstance()->AddRenderable(gobletModel);
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

			if (generator.IsStart(i, j))
			{
				RenderingEngine::Camera::GetInstance()->SetPosition({i, j, 1.8f});
			}

			if (generator.IsGoblet(i, j))
			{
				AddGoblet({ i, j });
			}
		}
	}
}

static void OnGameStart()
{
	wallObjFile = RenderingEngine::LoadOBJ(WALL_OBJ);
	wallMesh.UploadOBJ(wallObjFile);

	wallImage = new RenderingEngine::Image(BRICK_WALL_JPG);

	wallTexture = new RenderingEngine::OpenGL::Texture;

	wallTexture->Image2D(wallImage->GetPixels(),
		RenderingEngine::OpenGL::DataType::UnsignedByte,
		RenderingEngine::OpenGL::Format::RGBA,
		wallImage->GetWidth(),
		wallImage->GetHeight(),
		RenderingEngine::OpenGL::InternalFormat::RGBA);

	wallTexture->SetWrappingR(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	wallTexture->SetWrappingS(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	wallTexture->SetWrappingT(RenderingEngine::OpenGL::Wrapping::MirroredRepeat);
	wallTexture->SetFilters(RenderingEngine::OpenGL::Filter::LinearMipmapNearest, RenderingEngine::OpenGL::Filter::NearestMipmapLinear);
	wallTexture->GenerateMipmaps();

	AddLabyrinth();
}

static void OnGameEnd()
{
	for (auto& model : wallModels)
	{
		delete model;
	}
	
	delete wallTexture;
	delete wallImage;

	delete gobletImage;
	delete gobletTexture;
	delete gobletModel;
}

static void OnFrame(uint32_t deltaTime)
{
	(void) deltaTime;

	glm::vec3 camPos = RenderingEngine::Camera::GetInstance()->GetPosition();

	if (glm::length(camPos - gobletLocation) < 1.5f)
	{
		EventProcessing::Context::GetInstance()->RequestQuit();
	}
}

bool ModuleInit()
{
	EventProcessing::EventHandler::GetInstance()->RegisterOnFrameCallback(OnFrame);
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameStartCallback(OnGameStart);
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameEndCallback(OnGameStart);
	return true;
}
