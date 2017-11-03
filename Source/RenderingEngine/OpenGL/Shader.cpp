#include <RenderingEngine/OpenGL/Shader.hpp>

namespace RenderingEngine::OpenGL
{
	Shader::Shader(const ShaderType shaderType)
	{
		m_ObjectID = glCreateShader(GLenum(shaderType));
		if(m_ObjectID == 0)
		{
			throw Exception("Shader creation failed!");
		}
	}

	Shader::~Shader()
	{
		glDeleteShader(m_ObjectID);
	}

	const GLuint Shader::Handle() const
	{
		return m_ObjectID;
	}

	void Shader::Source(const std::string& code)
	{
		const char* c = code.c_str();
		auto length = (int) code.length();
		glShaderSource(m_ObjectID, 1, &c, &length);
	}

	void Shader::Compile()
	{
		GLint res;
		glCompileShader(m_ObjectID);
		glGetShaderiv(m_ObjectID, GL_COMPILE_STATUS, &res);

		if (res != GL_TRUE)
        {
			throw Exception(GetInfoLog());
		}
	}

	std::string Shader::GetInfoLog()
	{
		GLint res;
		glGetShaderiv(m_ObjectID, GL_INFO_LOG_LENGTH, &res);

		if(res <= 0) return "";

		std::string infoLog(res, 0);
		glGetShaderInfoLog(m_ObjectID, res, &res, &infoLog[0]);
		return infoLog;
	}
}
