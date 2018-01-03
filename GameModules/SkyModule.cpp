#include <Infrastructure/GameModule.hpp>

#include <RenderingEngine\RenderingEngine.hpp>
#include <RenderingEngine\Mesh\ObjLoader.hpp>
#include <RenderingEngine\Mesh\Mesh.hpp>
#include <RenderingEngine\Renderables\Model.hpp>
#include <RenderingEngine\Image\Image.hpp>

#include <RenderingEngine\Camera.hpp>

std::vector<RenderingEngine::Vertex> objFile;
RenderingEngine::Mesh mesh;
RenderingEngine::Model* model;
RenderingEngine::Image* image;
RenderingEngine::OpenGL::Texture* texture;

static void OnGameStart()
{
	objFile = RenderingEngine::LoadOBJ("../Assets/obj/SkyBox/SkyBox.obj");
	mesh.UploadOBJ(objFile);

	model = new RenderingEngine::Model;
	model->UploadMesh(mesh);

	image = new RenderingEngine::Image("../Assets/textures/skybox.png");

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

bool ModuleInit()
{
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameStartCallback(OnGameStart);
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameEndCallback(OnGameEnd);
	EventProcessing::EventHandler::GetInstance()->RegisterOnFrameCallback(OnFrame);
	return true;
}
