//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_TEXTUREBASE_H
#define PABLO_RENDERER_TEXTUREBASE_H

#include "Renderer/Utils/OGLObject/OGLObject.h"
#include "iostream"
#include "stb_image.h"
#include "stb_image_write.h"
#include "Debug/DebugLogger.h"
#include "mutex"

/***
 * Base class for the Texutres used by the application
 * @inherit OGLObject
 */
class TextureBase : public OGLObject {
public:
    TextureBase() {this->samplerID = 0;};

    /***
     * ID generated by OpenGL
     */
    GLuint ID;

    /***
     * Type of the texture as GL_ENUM_TEX used for opengl operations
     */
    GLenum type;

    /***
     * @brief Represents format of the texture can be GL_RED, GL_RGB, GL_RGBA
     */
    GLenum format;

    /***
     * Handler generated by bind-less textures
     */
    GLint64 handler;

    /***
     * Gl texuture type enum value represented as the string
     */
    std::string type_string;

    /***
     * Name of unifrom sampler in shader
     */
    std::string shaderName;

    /***
     * Sampler if the texture to be used in shader
     * this might be 0 or unused in some cases as the PBR material struct is sometimes handling samplers
     */
    unsigned int samplerID;

    /***
     * @brief Boolean flag that marks if texture was found or not
     */
    bool wasFound;

    /***
     * @brief Boolean flag that marks if the texture represents PBR material
     */
    bool isPBRMaterial;

    /***
     * @brief Full path to the texture
     */
    std::string fullPath;

    /***
     * @brief Relative path of the textue to the directory of the model
     * @note empty if texture is not part of the model
     */
    std::string relativePath = "";

    /***
     * @brief Dimensions of the texture
     */
    int texWidth, texHeight;

    /***
     * Changes minifaction and magnification filtering method
     * @param mag filtering method to use for Magnification
     * @param min filtering method to use for Minification
     */
    void changeFilteringMethod(GLenum mag, GLenum min);

    /**
     * Binds the ID to the GL_TEXTURE_TARGET specified as a target property
     */
    void bind() override;

    /***
     * Binds target to 0
     */
    void unbind() override;

    /***
     * Generate mipmaps for the texture
     */
    void generateMipMaps();

    /***
     * Sets unpacking alignment
     * @param alignment valid values are 0,2,4,6,8
     */
    void setUnpackAlignment(int alignment);

    void clearTextureData() { stbi_image_free(this->textureData);}

    /***
    * @brief Loads texture data that are stored to the opengl texture object
    * @note only applies to the the texture data expressed in unsigned char
    */
    virtual void passToOpenGL(){};

    unsigned int getSamplerID() const { return this->samplerID; }

    void setSamplerID(unsigned int ID) { this->samplerID = ID; }

    const std::string &getFullPath() const { return this->fullPath; };

    unsigned char* getData() {return this->textureData;}
protected:

    /***
     * Loads PNG image to the texture
     * @param path path to the texture that needs to be loaded with file extension .png
     * @param flip should the loader flip the image texture @def false
     */
    void loadPNG(const char*path,bool loadToGl = true ,bool flip = false);

    /***
     * Loads equirectangular HDR texture
     * @param path path to the texture that needs to be loaded with file extension .hdr
     */
    void loadHRI(const char*path);

    /***
     * @brief Here should actual texture data be stored but they should be removed when loaded to the GPU
     */
    unsigned char *textureData = nullptr;

private:
    void release() {
        if (ID != 0) {
            stbi_image_free(this->textureData);
        }
    };

public:
    //------------------------
    // C++ RULE 3/5 PRINCIPLES
    //------------------------
    ~TextureBase() = default; //{ release(); }

    TextureBase(const TextureBase &) = default;

    TextureBase &operator=(const TextureBase &) = delete;

    TextureBase(TextureBase &&other) noexcept;

    TextureBase &operator=(TextureBase &&other) noexcept;
};


#endif //PABLO_RENDERER_TEXTUREBASE_H
