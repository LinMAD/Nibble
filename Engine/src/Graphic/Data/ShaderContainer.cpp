#include "pch.h"
#include "ShaderContainer.h"

namespace Nibble {
	ShaderContainer::~ShaderContainer()
	{
		DeleteAll();
	}

	void ShaderContainer::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		M_NIBBLE_ENG_ASSERT(!Exists(name), "Already exists:" + name);
		m_Shaders[name] = shader;
	}
	
	void ShaderContainer::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	std::shared_ptr<Shader> ShaderContainer::Load(const std::string& vertexPath, const std::string& fragmentPath)
	{
		auto shader = Shader::CreateFromFile(vertexPath, fragmentPath);

		Add(shader);

		return shader;
	}

	std::shared_ptr<Shader> ShaderContainer::Load(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
	{
		auto shader = Shader::CreateFromFile(vertexPath, fragmentPath, geometryPath);

		Add(shader);

		return shader;
	}
	
	std::shared_ptr<Shader> ShaderContainer::Get(const std::string& name)
	{
		M_NIBBLE_ENG_ASSERT(Exists(name), "Not found: " + name);
		return m_Shaders[name];
	}
	
	bool ShaderContainer::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	void ShaderContainer::DeleteAll()
	{
		m_Shaders.clear();
	}
}
