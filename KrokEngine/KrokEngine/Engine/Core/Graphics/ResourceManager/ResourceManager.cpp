#include "ResourceManager.hpp"
#include "PathManager.hpp"
#include "ResourceCache/ResourceCache.hpp"

#include "../Core/texture/Texture.hpp"
#include "../Core/Shader/Shader.hpp"
#include "../Core/GLBuffer/GLBuffer.hpp"

#include "../loaders/ShaderUtil.hpp"

Texture ResourceManager::GetTexture(const unsigned int a_uniqueID)
{
    std::string path = PathManager::GetFilePath(a_uniqueID);

    if (!pTexureCache) return Texture(path);    //If no cache exists, create and return a new texture

    if (pTexureCache->Exists(path)){
        //std::cout << "ResourceManager: " << path << " already cached, not loaded again" << std::endl;
        return pTexureCache->Get(path);
    }

    Texture texture(path);
    pTexureCache->AddNewResource(path, texture);
    return texture;
}

Shader ResourceManager::GetShader(const unsigned int a_vertexhaderPathID, const unsigned int a_fragmentShaderPathID)
{
    std::string path = ShaderUtil::createString(PathManager::GetFilePath(a_vertexhaderPathID), PathManager::GetFilePath(a_fragmentShaderPathID));

    if (!pShaderCache) return Shader(path);    //If no cache exists, create and return a new shader

    if (pShaderCache->Exists(path))  {
        //std::cout << "ResourceManager: " << path << " already cached, not loaded again" << std::endl;
        return pShaderCache->Get(path);
    }

    Shader shader(path);
    pShaderCache->AddNewResource(path, shader);
    return shader;
}

GLBuffer ResourceManager::GetGLBuffer(const unsigned int a_displayModeID)
{
    DisplayMode displayMode = DisplayMode(a_displayModeID);

    if (!pGLBufferCache) return GLBuffer(displayMode);    //If no cache exists, create and return a new glBuffer

    if (pGLBufferCache->Exists(a_displayModeID)) {
        //std::cout << "ResourceManager: " << displayMode << " already cached, not loaded again" << std::endl;
        return pGLBufferCache->Get(a_displayModeID);
    }

    GLBuffer bufffer(displayMode);
    pGLBufferCache->AddNewResource(a_displayModeID, bufffer);

    return bufffer;
}
