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
        explicit Model(char *path);
        void Draw(ShaderProgram &program);

    private:
        std::vector<Mesh> m_meshes;
        std::string m_directory;
        std::vector<GLTexture> m_loadedTextures;

        void Load(std::string path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<GLTexture> LoadMaterialTextures(aiMaterial *material, aiTextureType assimpType, GLTextureType localType);
    };
}