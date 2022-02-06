#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Asset/AssetManager.hpp"
#include "Exception/Exception.hpp"
#include "GL/GLTexture.hpp"
#include "GL/Model.hpp"
#include "GL/Texture.hpp"

using namespace Iris;

Model::Model(const std::string& path)
{
    Load(path);
}

void Model::Draw(const std::shared_ptr<ShaderProgram>& program)
{
    for (auto & mesh : m_meshes)
    {
        mesh.Draw(program);
    }
}

std::vector<GLTexture> Model::GetLoadedTextures()
{
    return m_loadedTextures;
}

void Model::Load(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw Exception(importer.GetErrorString());
    }

    m_directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<GLVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GLTexture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        GLVertex vertex{
            .position = vector
        };

        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        if (mesh->mTextureCoords[0])
        {
            vertex.texCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
        {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<GLTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, GLTextureType::Diffuse);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<GLTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, GLTextureType::Specular);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<GLTexture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, GLTextureType::Normal);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<GLTexture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, GLTextureType::Height);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    std::vector<GLTexture> emissionMaps = LoadMaterialTextures(material, aiTextureType_EMISSIVE, GLTextureType::Emission);
    textures.insert(textures.end(), emissionMaps.begin(), emissionMaps.end());

    return {vertices, indices, textures};
}

std::vector<GLTexture> Model::LoadMaterialTextures(aiMaterial *material, aiTextureType assimpType, GLTextureType localType)
{
    std::vector<GLTexture> glTextures;
    for (unsigned int i = 0; i < material->GetTextureCount(assimpType); i++)
    {
        aiString str;
        material->GetTexture(assimpType, i, &str);
        bool skip = false;
        for (auto & m_loadedTexture : m_loadedTextures)
        {
            if (std::strcmp(m_loadedTexture.path, str.C_Str()) == 0)
            {
                glTextures.push_back(m_loadedTexture);
                skip = true;
                break;
            }
        }

        if (skip) continue;

        AssetManager& assetManager = AssetManager::GetInstance();
        std::shared_ptr<Texture> texture = assetManager.GenerateTexture(m_directory + '/' + str.C_Str());

        GLTexture glTexture = {
            .texture = texture,
            .type = localType,
            .path = str.C_Str()
        };

        glTextures.push_back(glTexture);
        m_loadedTextures.push_back(glTexture);
    }

    return glTextures;
}
