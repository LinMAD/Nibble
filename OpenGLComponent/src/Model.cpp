#include "Model.h"

Model::Model()
{
}

void Model::renderModel()
{
	for (size_t i = 0; i < m_meshList.size(); i++)
	{
		unsigned int materialIndex = m_meshToTex[i];

		if (materialIndex < m_textureList.size() && m_textureList[materialIndex])
		{
			m_textureList[materialIndex]->useTexture();
		}

		m_meshList[i]->renderMesh();
	}
}

void Model::loadModel(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
		return;
	}

	loadNode(scene->mRootNode, scene);

	loadMaterials(scene);
}

void Model::loadNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		loadNode(node->mChildren[i], scene);
	}
}

void Model::loadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh();
	newMesh->createMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	m_meshList.push_back(newMesh);
	m_meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene* scene)
{
	m_textureList.resize(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		m_textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") + filename;

				m_textureList[i] = new Texture(texPath.c_str());

				if (!m_textureList[i]->loadTexture())
				{
					printf("Failed to load texture at: %s\n", texPath);
					delete m_textureList[i];
					m_textureList[i] = nullptr;
				}
			}
		}

		if (!m_textureList[i])
		{
			m_textureList[i] = new Texture("Textures/missing.png");
			m_textureList[i]->loadTextureWithAlpha();
		}
	}
}

void Model::clearModel()
{
	for (size_t i = 0; i < m_meshList.size(); i++)
	{
		if (m_meshList[i])
		{
			delete m_meshList[i];
			m_meshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < m_textureList.size(); i++)
	{
		if (m_textureList[i])
		{
			delete m_textureList[i];
			m_textureList[i] = nullptr;
		}
	}
}

Model::~Model()
{
}