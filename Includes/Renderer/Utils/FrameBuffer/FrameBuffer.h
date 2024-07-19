//
// Created by wpsimon09 on 05/02/24.
//

#ifndef PABLO_RENDERER_FRAMEBUFFER_H
#define PABLO_RENDERER_FRAMEBUFFER_H

#include "glad/glad.h"
#include "RenderBuffer/RenderBuffer.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "Shader.h"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Geometry/Shapes/ScreenSpaceQuad/ScreenSpaceQuadGeometry.h"
#include "Renderer/Material/BasicMaterialTexturd/BasicMaterialTextured.h"

/***
 * Class representing GL_FRAMEBUFFER encapsulation
 * This class represent 2D frame buffer which is rendering to the GL_TEXTURE_2D color attachement
 * contains most of the operations that can be preformed on the GL_FRAMEBUFFER object
 */
class FrameBuffer : public OGLObject, public Renderable {
public:
    /***
     * ID generated by OpenGL
     */
    GLuint ID;

    /***
     * Field marking if frame buffer has color attachment or not
     */
    bool isDepthOnly = false;

    /***
     * Creates frame buffer instance
     * @param SCR_WIDTH width of the frame buffer
     * @param SCR_HEIGHT height of the frame buffer
     * @param customShader shader to be used during rendering the frame buffer color attachment
     * @param customColorAttachement texture to be used as a color attachment which can be later retried
     * @param generateMipMapChain true if colour attachment of the frame buffer should be texture with generated mip chain
     */
    FrameBuffer(int SCR_WIDTH, int SCR_HEIGHT, std::shared_ptr<Shader> customShader = nullptr,std::unique_ptr<Texture2D> customColorAttachement = nullptr, bool generateMipMapChain = false, int levels = 6 );

    /***
     * Gets the result of the rendering to this frame buffer
     * this is call is valid after drawing to renderbuffer was preformed
     * @return result of the rendering process
     */
    std::shared_ptr<Texture2D> getRenderedResult();

    /***
     * Binds the frame buffer's ID to the GL_FRAMEBUFFER target
     */
    void bind() override;

    /***
     * Binds GL_FRAMEBUFFER target to 0
     */
    void unbind() override;

    /***
     * Sets the shader that should be used while preforming rendering
     * @param shader shader to be used
     */
    void setShader(std::shared_ptr<Shader> shader);

    /***
     * Renders the frame buffer to the default frame buffer which is 0
     * render frame buffer will cover the size of the provided width and height of the constructor and use plane geometry that is covering the whole screen
     * together with Basic textured material
     */
    void dispalyOnScreen();

    /***
     * Preforms rendering to itself and stores rendered result to the texture
     */
    void drawInsideSelf(bool useColourAttachemntAsTexture =true);

    /**
     * @brief Updates the dimentions of the frame buffer
     * @param width new widht
     * @param height new height
     */
    void updateDimetions(float width, float height);

     /***
     * Sets the color attachment of frame buffer that is supposed to be rendered
     * @param colorAttachment color attachment to use
     */
    void setColorAttachment(std::shared_ptr<Texture2D> colorAttachment);

    /***
     * Changes filtering method of the color attachment
     * @param mag magnification filter GL_LINEAR, GL_CLAMP_TO_EDGE etc...
     * @param min minification filter GL_LINEAR, GL_CLAMP_TO_EDGE etc...
     */
    void changeFilteringMethod(GLenum mag, GLenum min);

    /***
     * Gets rid of the color attachment of the frame buffer and only writes the depth values of the objects
     */
    void makeDepthOnly(std::shared_ptr<Texture2D> depthMapTexture = nullptr);

    /***
     * Saves the frame buffer collor buffer to the PNG inside the specified path
     * @param path path into which the png will be stored
     */
    void saveAsPNG(std::string path);

    void setCurrentMipLevel(std::shared_ptr<Texture2D> texture, int mipLevel);

    void transferToGbufferSupport(std::shared_ptr<Texture2D> gPosition, std::shared_ptr<Texture2D> gNormal, std::shared_ptr<Texture2D> gSpecularAndShininess, std::shared_ptr<Texture2D>gMetalnessRougness , std::shared_ptr<Texture2D> depthMap = nullptr);

    bool hasGBufferSupport(){return supportsGBuffer;}

    std::vector<std::shared_ptr<Texture2D>> getGBufferTextures();

    int getWidht() {return this->width;}
    int getHeihgt() {return this->height;}
protected:
    std::shared_ptr<Shader> shader;
    std::unique_ptr<RenderBuffer> renderBuffer;
    std::shared_ptr<Texture2D> colorAttachment;

    std::vector<std::shared_ptr<Texture2D>> colourAttachemnts;

    bool supportsGBuffer = false;

    int width, height;
private:
    void clear() {
        //glDeleteFramebuffers(1, &this->ID);
        //this->ID;
    };

    bool checkFrameBufferCompleteness();
public:
    //-------------
    // C++ RULE 3/5
    //-------------
    ~FrameBuffer(){};
    FrameBuffer(const FrameBuffer &) = delete;

    FrameBuffer &operator=(const FrameBuffer &) = delete;

    FrameBuffer(FrameBuffer &&other);
    FrameBuffer& operator =(FrameBuffer &&other) noexcept ;
};


#endif //PABLO_RENDERER_FRAMEBUFFER_H
