#pragma once

#include <vector>
#include <string>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
private:
	void loadNode(aiNode* node, const aiScene* scene);
	void loadMesh(aiMesh* mesh, const aiScene* scene);
	void loadMaterials(const aiScene* scene);

	std::vector<Mesh*> m_meshList;
	std::vector<Texture*> m_textureList;
	std::vector<unsigned int> m_meshToTex;
public:
	Model();

	void loadModel(const std::string& fileName);
	void renderModel();
	void clearModel();

	~Model();
};
