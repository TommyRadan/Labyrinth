#pragma once

#include <RenderingEngine/OpenGL/Typedef.hpp>

#include <exception>
#include <string>

#include <Infrastructure/Exception.hpp>

namespace RenderingEngine::OpenGL
{
	struct Shader
	{
		explicit Shader(ShaderType type);
		~Shader();
		
		const GLuint Handle() const;
		
		void Source(const std::string& code);
		void Compile();

		std::string GetInfoLog();

	private:
		GLuint m_ObjectID;
	};
}
