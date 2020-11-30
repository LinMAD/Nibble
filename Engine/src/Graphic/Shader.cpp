#include "pch.h"
#include "Shader.h"
#include "OpenGL/GLShader.h"
#include "Renderer.h"

namespace Nibble {
	std::shared_ptr<Shader> Shader::Create(
		const std::string& name,
		const std::string& vertexSrc,
		const std::string& fragmentSrc
	)
	{
		// TODO Implement from string shader creation
		M_NIBBLE_ENG_ASSERT(false, "Not implemented");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::CreateFromFile(
		const std::string& vertexPath, 
		const std::string& fragmentPath
	)
	{
		if (Renderer::GetType() == Renderer::Type::OpenGL)
			return std::make_shared<GLShader>(vertexPath, fragmentPath);

		M_NIBBLE_ENG_ASSERT(false, "Unknown renderer graphical API");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::CreateFromFile(
		const std::string& vertexPath,
		const std::string& fragmentPath,
		const std::string& geometryPath
	)
	{
		if (Renderer::GetType() == Renderer::Type::OpenGL)
			return std::make_shared<GLShader>(vertexPath, fragmentPath, geometryPath);

		M_NIBBLE_ENG_ASSERT(false, "Unknown renderer graphical API");
		return nullptr;
	}
}
