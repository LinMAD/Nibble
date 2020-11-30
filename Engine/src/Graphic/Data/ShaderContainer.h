#pragma once

#include "Graphic/Shader.h"

namespace Nibble {
	class ShaderContainer
	{
	public:
		~ShaderContainer();
		void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
		void Add(const std::shared_ptr<Shader>& shader);

		std::shared_ptr<Shader> Load(
			const std::string& vertexPath,
			const std::string& fragmentPath
		);

		std::shared_ptr<Shader> Load(
			const std::string& vertexPath,
			const std::string& fragmentPath,
			const std::string& geometryPath
		);

		std::shared_ptr<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

		void DeleteAll();
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}
