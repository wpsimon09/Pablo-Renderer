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

class FrameBuffer : public OGLObject, public Renderable {
public:
    GLuint ID;

    FrameBuffer(int SCR_WIDTH, int SCR_HEIGHT);

    const std::unique_ptr<Texture2D> & getRenderedResult() const;

    void bind() override;

    void unbind() override;

    void setShader(std::unique_ptr<Shader> shader);

    void dispalyOnScreen();

    virtual void drawInsideSelf();

    void changeFilteringMethod(GLenum mag, GLenum min);
protected:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<RenderBuffer> renderBuffer;
    std::unique_ptr<Texture2D> colorAttachment;
    int width, height;
private:
    void clear() {
        //glDeleteFramebuffers(1, &this->ID);
        //this->ID;
    };

public:
    //-------------
    // C++ RULE 3/5
    //-------------
    FrameBuffer(const FrameBuffer &) = delete;

    FrameBuffer &operator=(const FrameBuffer &) = delete;

    ~FrameBuffer() { this->clear(); }

    FrameBuffer(FrameBuffer &&other);
    FrameBuffer& operator =(FrameBuffer &&other) noexcept ;
};


#endif //PABLO_RENDERER_FRAMEBUFFER_H
