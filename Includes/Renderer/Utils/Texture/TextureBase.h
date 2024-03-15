//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_TEXTUREBASE_H
#define PABLO_RENDERER_TEXTUREBASE_H

#include "Renderer/Utils/OGLObject/OGLObject.h"
#include "iostream"
#include "stb_image.h"
#include "Debug/DebugLogger.h"

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
     * Handler generated by bind-less textures
     */
    GLint64 handler;

    /***
     * Gl texuture type enum value represented as the string
     */
    std::string type_string;

    /***
     * Sampler if the texture to be used in shader
     * this might be 0 or unused in some cases as the PBR material struct is sometimes handling samplers
     */
    unsigned int samplerID;

    bool wasFound;
    bool isPBRMaterial;
    std::string fullPath;
    int texWidth, texHeight;


    /***
     * Changes minifaction and magnification filtering method
     * @param mag filtering method to use for Magnification
     * @param min filtering method to use for Minification
     */
    void changeFilteringMethod(GLenum mag, GLenum min);

    unsigned int getSamplerID() const { return this->samplerID; }

    void setSamplerID(unsigned int ID) { this->samplerID = ID; }

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

    const std::string &getFullPath() const { return this->fullPath; };
protected:

    /***
     * Loads PNG image to the texture
     * @param path path to the texture that needs to be loaded with file extension .png
     * @param flip should the loader flip the image texture @def false
     */
    void loadPNG(const char*path, bool flip = false);

    /***
     * Loads equirectangular HDR texture
     * @param path path to the texture that needs to be loaded with file extension .hdr
     */
    void loadHRI(const char*path);

private:
    void release() {
        if (ID != 0) {
            // Reset ID to indicate that the texture has been released
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
