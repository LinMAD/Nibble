#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Nibble {
	/// <summary>
	/// Common abstract shader
	/// </summary>
	class Shader {
	public:
		/// <summary>
		/// Data types used for dynamic usages of when working with shader code
		/// </summary>
		enum class DataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

		virtual ~Shader() = default;

		virtual void Lock() const = 0;
		virtual void Unlock() const = 0;

		virtual const std::string& GetName() const = 0;

		static std::shared_ptr<Shader> Create(
			const std::string& name, 
			const std::string& vertexSrc, 
			const std::string& fragmentSrc
		);
		static std::shared_ptr<Shader> CreateFromFile(
			const std::string& vertexPath, 
			const std::string& fragmentPath
		);
		static std::shared_ptr<Shader> CreateFromFile(
			const std::string& vertexPath, 
			const std::string& fragmentPath,
			const std::string& geometryPath
		);

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static int ToNativeShaderType(DataType type)
		{
			M_NIBBLE_ENG_ASSERT("Must be implemented in concrete shader");
		}

		/// <summary>
		/// Return byte representation of type
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		static uint32_t DataTypeSize(DataType type)
		{
			switch (type)
			{
			case DataType::Float:    return 4;
			case DataType::Float2:   return 4 * 2;
			case DataType::Float3:   return 4 * 3;
			case DataType::Float4:   return 4 * 4;
			case DataType::Mat3:     return 4 * 3 * 3;
			case DataType::Mat4:     return 4 * 4 * 4;
			case DataType::Int:      return 4;
			case DataType::Int2:     return 4 * 2;
			case DataType::Int3:     return 4 * 3;
			case DataType::Int4:     return 4 * 4;
			case DataType::Bool:     return 1;
			}

			M_NIBBLE_ENG_ASSERT("Unknown ShaderDataTypeSize");
			return 0;
		}
	protected:
		uint32_t m_RendererId;
		std::string m_Name;
	};
}
