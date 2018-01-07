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

#ifdef _DEBUG
#define GRASS_PNG "../Assets/textures/grass.png"
#elif _RELEASE
#define GRASS_PNG "../Assets/textures/grass.png"
#elif _DEPLOY
#define GRASS_PNG "Assets/textures/grass.png"
#endif

static void OnGameStart()
{
	model = new RenderingEngine::Model;
	model->UploadMesh(RenderingEngine::GenerateTerrain());

	image = new RenderingEngine::Image(GRASS_PNG);
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

GAME_MODULE()
{
	REGISTER_CALLBACK(OnGameStart, OnGameStart);
	REGISTER_CALLBACK(OnGameEnd, OnGameStart);
	return true;
}
