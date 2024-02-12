//
// Created by wpsimon09 on 05/02/24.
//

#ifndef PABLO_RENDERER_FRAMEBUFFER_H
#define PABLO_RENDERER_FRAMEBUFFER_H

#include "glad/glad.h"
#include "RenderBuffer/RenderBuffer.h"
#include "Renderer/Utils/Texture/Texture2D.h"
#include "Shader.h"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Geometry/Shapes/ScreenSpaceQuad/ScreenSpaceQuadGeometry.h"
#include "Renderer/Material/BasicMaterialTexturd/BasicMaterialTextured.h"

class FrameBuffer: public OGLObject, public Renderable {
public:
    GLuint ID;
    FrameBuffer(int SCR_WIDTH, int SCR_HEIGHT);
    Texture2D getRenderedResult();

    void bind() override;
    void unbind() override;
    void setShader(Shader* shader);

    void dispalyOnScreen();

    void drawInsideSelf();

protected:
    Shader *shader ;
    RenderBuffer* renderBuffer;
    Texture2D colorAttachment;

    int width, height;
};


#endif //PABLO_RENDERER_FRAMEBUFFER_H
