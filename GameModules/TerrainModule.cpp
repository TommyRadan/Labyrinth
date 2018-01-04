#include <Infrastructure/GameModule.hpp>

#include <RenderingEngine\Mesh\TerrainGenerator.hpp>

#include <RenderingEngine\RenderingEngine.hpp>
#include <RenderingEngine\Mesh\ObjLoader.hpp>
#include <RenderingEngine\Mesh\Mesh.hpp>
#include <RenderingEngine\Renderables\Model.hpp>
#include <RenderingEngine\Image\Image.hpp>

static RenderingEngine::Model* model;
static RenderingEngine::Image* image;
static RenderingEngine::OpenGL::Texture* texture;

static void OnGameStart()
{
	model = new RenderingEngine::Model;
	model->UploadMesh(RenderingEngine::GenerateTerrain());

	image = new RenderingEngine::Image("../Assets/textures/grass.png");
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

	model->options.Textures["tex"] = texture;

	RenderingEngine::Context::GetInstance()->AddRenderable(model);
}

static void OnGameEnd()
{
	delete model;
	delete texture;
	delete image;
}

bool ModuleInit()
{
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameStartCallback(OnGameStart);
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameEndCallback(OnGameStart);
	return true;
}
