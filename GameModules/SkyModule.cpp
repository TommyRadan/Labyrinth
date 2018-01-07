#include <Infrastructure/GameModule.hpp>

#include <RenderingEngine\RenderingEngine.hpp>
#include <RenderingEngine\Mesh\ObjLoader.hpp>
#include <RenderingEngine\Mesh\Mesh.hpp>
#include <RenderingEngine\Renderables\Model.hpp>
#include <RenderingEngine\Image\Image.hpp>

#include <RenderingEngine\Camera.hpp>

static std::vector<RenderingEngine::Vertex> objFile;
static RenderingEngine::Mesh mesh;
static RenderingEngine::Model* model;
static RenderingEngine::Image* image;
static RenderingEngine::OpenGL::Texture* texture;

#ifdef _DEBUG
#define SKYBOX_OBJ "../Assets/obj/SkyBox/SkyBox.obj"
#define SKYBOX_PNG "../Assets/textures/skybox.png"
#elif _RELEASE
#define SKYBOX_OBJ "../Assets/obj/SkyBox/SkyBox.obj"
#define SKYBOX_PNG "../Assets/textures/skybox.png"
#elif _DEPLOY
#define SKYBOX_OBJ "Assets/obj/SkyBox/SkyBox.obj"
#define SKYBOX_PNG "Assets/textures/skybox.png"
#endif

static void OnGameStart()
{
	objFile = RenderingEngine::LoadOBJ(SKYBOX_OBJ);
	mesh.UploadOBJ(objFile);

	model = new RenderingEngine::Model;
	model->UploadMesh(mesh);

	image = new RenderingEngine::Image(SKYBOX_PNG);

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

	model->SetRotation(glm::vec3(3.14f, 0.0f, 0.0f));
	model->SetScale(glm::vec3(100.0f, 100.0f, 100.0f));
	
	RenderingEngine::Context::GetInstance()->AddRenderable(model);
}

static void OnGameEnd()
{
	delete model;
	delete texture;
	delete image;
}

static void OnFrame(uint32_t deltaTime)
{
	(void) deltaTime;

	model->SetPosition(RenderingEngine::Camera::GetInstance()->GetPosition());
}

GAME_MODULE()
{
	REGISTER_CALLBACK(OnGameStart, OnGameStart);
	REGISTER_CALLBACK(OnGameEnd, OnGameEnd);
	REGISTER_CALLBACK(OnFrame, OnFrame);
	return true;
}
