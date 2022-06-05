#pragma once

#include <string>
#include <vector>

#include <assimp/scene.h>

#include "Data/TextureData.hpp"
#include "Mesh.hpp"
#include "Shader/ShaderProgram.hpp"

namespace Iris::GL
{
    class Model
    {
    public:
        explicit Model(const std::string& path);
        void Draw(const std::shared_ptr<ShaderProgram> &program);
        std::vector<TextureData> GetLoadedTextures();

    private:
        std::vector<Mesh> m_meshes;
        std::string m_directory;
        std::vector<TextureData> m_loadedTextures;

        void Load(const std::string& path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<TextureData> LoadMaterialTextures(aiMaterial *material, aiTextureType assimpType, TextureDataType localType);
    };
}
