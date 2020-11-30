#include "pch.h"
#include "GLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Nibble {
	GLShader::GLShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexString = ReadFile(vertexPath);
		std::string fragmentString = ReadFile(fragmentPath);

		CompileShader(vertexString.c_str(), fragmentString.c_str());
	}

	GLShader::GLShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
	{
		std::string vertexString = ReadFile(vertexPath);
		std::string fragmentString = ReadFile(fragmentPath);
		std::string geometryString = ReadFile(geometryPath);

		CompileShader(vertexString.c_str(), fragmentString.c_str(), geometryString.c_str());
	}

	GLShader::~GLShader()
	{
		for (auto id : m_glShaderIDs)
		{
			glDetachShader(m_RendererId, id);
			glDeleteShader(id);
		}
		glDeleteProgram(m_RendererId);
	}

	std::string GLShader::ReadFile(const std::string& filepath)
	{
		std::string content;
		std::ifstream fileStream(filepath, std::ios::in);

		if (!fileStream.is_open()) {
			M_NIBBLE_ENG_ASSERT("Could not open file '{0}'", filepath);
			return "";
		}

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto firstDot = filepath.find('.');
		auto count = firstDot == std::string::npos ? filepath.size() - lastSlash : firstDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);

		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();

		return content;
	}

	void GLShader::CompileShader(const char* vertexCode, const char* fragmentCode)
	{
		m_RendererId = glCreateProgram();
		if (!m_RendererId)
		{
			printf("Error creating shader program!\n");
			M_NIBBLE_ENG_ASSERT(false, "Error compiling shader");
			return;
		}

		AddShader(m_RendererId, vertexCode, GL_VERTEX_SHADER);
		AddShader(m_RendererId, fragmentCode, GL_FRAGMENT_SHADER);

		LinkShaderProgram();
	}

	void GLShader::CompileShader(const char* vertexCode, const char* fragmentCode, const char* geometryCode)
	{
		m_RendererId = glCreateProgram();
		if (!m_RendererId)
		{
			printf("Error creating shader program!\n");
			M_NIBBLE_ENG_ASSERT(false, "Error compiling shader");
			return;
		}

		AddShader(m_RendererId, vertexCode, GL_VERTEX_SHADER);
		AddShader(m_RendererId, fragmentCode, GL_FRAGMENT_SHADER);
		AddShader(m_RendererId, geometryCode, GL_GEOMETRY_SHADER);

		LinkShaderProgram();
	}

	void GLShader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		const GLchar* theCode[1]{};
		theCode[0] = shaderCode;

		GLint codeLength[1]{};
		codeLength[0] = static_cast<GLint>(strlen(shaderCode));

		glShaderSource(shader, 1, theCode, codeLength);
		glCompileShader(shader);

		GLint result = 0;
		GLchar eLog[1024] = { 0 };

		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);

			M_LOGGER_ENG_ERROR("Error compiling the {0} shader: '{1}'", shaderType, eLog);
			M_NIBBLE_ENG_ASSERT(false, "Error compiling shader");
			return;
		}

		glAttachShader(theProgram, shader);
		m_glShaderIDs[m_glShaderIdIndex++] = shader;
	}

	void GLShader::LinkShaderProgram()
	{
		glLinkProgram(m_RendererId);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);

			// Clean up
			glDeleteProgram(m_RendererId);
			for (auto id : m_glShaderIDs) 
				glDeleteShader(id);

			M_LOGGER_ENG_ERROR("Failed to compile fragment shader, error: {0}", infoLog.data());
			M_NIBBLE_ENG_ASSERT(false, "Shader link failure!");
			return;
		}

		// Clean up
		for (auto id : m_glShaderIDs)
		{
			glDetachShader(m_RendererId, id);
			glDeleteShader(id);
		}
	}

	void GLShader::Lock() const
	{
		glUseProgram(m_RendererId);
	}

	void GLShader::Unlock() const
	{
		glUseProgram(0);
	}

	void GLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(location, value);
	}

	void GLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1iv(location, count, values);
	}

	void GLShader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(location, value);
	}

	void GLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void GLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void GLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void GLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void GLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
