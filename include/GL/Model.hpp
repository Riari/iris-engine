#pragma once

#include <string>
#include <vector>

#include <assimp/scene.h>

#include "GLTexture.hpp"
#include "Mesh.hpp"
#include "Shader/ShaderProgram.hpp"

namespace Iris
{
    class Model
    {
    public:
        explicit Model(const std::string& path);
        void Draw(const std::shared_ptr<ShaderProgram> &program);
        std::vector<GLTexture> GetLoadedTextures();

    private:
        std::vector<Mesh> m_meshes;
        std::string m_directory;
        std::vector<GLTexture> m_loadedTextures;

        void Load(const std::string& path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<GLTexture> LoadMaterialTextures(aiMaterial *material, aiTextureType assimpType, GLTextureType localType);
    };
}