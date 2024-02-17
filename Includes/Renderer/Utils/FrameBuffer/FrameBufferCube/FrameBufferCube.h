//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_FRAMEBUFFERCUBE_H
#define PABLO_RENDERER_FRAMEBUFFERCUBE_H

#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"

#include "Renderer/Geometry/Shapes/Cube/CubeGeometry.h"
#include "Renderer/Utils/Texture/Texture3D/Texture3D.h"
#include "Renderer/Utils/ShaderHelper/ShaderHelper.h"
#include "Renderer/Utils/FrameBuffer/RenderBuffer/RenderBuffer.h"

class FrameBufferCube:public OGLObject {
public:
    FrameBufferCube(int width, int height, Shader* shader, Texture3D texture,unsigned int mipLevels = 0);
    GLuint ID;
    Texture3D renderToSelf(unsigned int mipLevel = 0);

    Texture3D colorAttachmentCube;
private:
    unsigned int mipLevels;
    Shader* shader;
    RenderBuffer* renderBuffer;
    Geometry* geometry;
    int width, height;
public:
    void clear(){}

    //-------------
    // C++ RULE 3/5
    //-------------
    FrameBufferCube(const FrameBufferCube &) = delete;
    FrameBufferCube &operator=(const FrameBufferCube &) = delete;

    ~FrameBufferCube(){ this->clear(); }

    FrameBufferCube(FrameBufferCube &&other) noexcept ;
    FrameBufferCube &operator= (FrameBufferCube &&other) noexcept;

    void bind() override;

    void unbind() override;

};

#endif //PABLO_RENDERER_FRAMEBUFFERCUBE_H
