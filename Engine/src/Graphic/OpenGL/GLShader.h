#pragma once
#include <glad/glad.h>
#include "Graphic/Shader.h"
#include "Traceability/Logger.h"

namespace Nibble {
	class GLShader : public Shader
	{
	public:
		GLShader(const std::string& vertexPath, const std::string& fragmentPath);
		GLShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);
		virtual ~GLShader();

		virtual void Lock() const override;
		virtual void Unlock() const override;

		virtual const std::string& GetName() const override 
		{ 
			return m_Name; 
		}

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;

		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		static int ToNativeShaderType(DataType type)
		{
			switch (type)
			{
			case Shader::DataType::Float:    return GL_FLOAT;
			case Shader::DataType::Float2:   return GL_FLOAT;
			case Shader::DataType::Float3:   return GL_FLOAT;
			case Shader::DataType::Float4:   return GL_FLOAT;
			case Shader::DataType::Mat3:     return GL_FLOAT;
			case Shader::DataType::Mat4:     return GL_FLOAT;
			case Shader::DataType::Int:      return GL_INT;
			case Shader::DataType::Int2:     return GL_INT;
			case Shader::DataType::Int3:     return GL_INT;
			case Shader::DataType::Int4:     return GL_INT;
			case Shader::DataType::Bool:     return GL_BOOL;
			}

			M_NIBBLE_ENG_ASSERT("Unknown Shader::DataType in OpenGL implementation!");
			return 0;
		}
	private:
		std::array<GLenum, 3> m_glShaderIDs;
		int m_glShaderIdIndex = 0;

		std::string ReadFile(const std::string& filepath);

		void CompileShader(const char* vertexCode, const char* fragmentCode);
		void CompileShader(const char* vertexCode, const char* fragmentCode, const char* geometryCode);
		
		void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
		
		void LinkShaderProgram();

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex") return GL_VERTEX_SHADER;
			if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

			M_NIBBLE_ENG_ASSERT(false, "Unknown shader type!");
			return 0;
		}
	};
}
