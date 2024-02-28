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
#include "memory"

class FrameBufferCube : public OGLObject {
public:
    FrameBufferCube(int width, int height, std::shared_ptr<Shader> shader, unsigned int mipLevels = 0);

    GLuint ID;

    std::shared_ptr<Texture3D> renderToSelf(TextureBase input, unsigned int mipLevel = 0);

    std::shared_ptr<Texture3D> colorAttachmentCube;

    void updateDimetions(unsigned int widht, unsigned int height);
private:
    unsigned int mipLevels;
    std::shared_ptr<Shader> shader;
    std::unique_ptr<RenderBuffer> renderBuffer;
    std::unique_ptr<Geometry> geometry;
    int width, height;
public:
    void clear() {}

    //-------------
    // C++ RULE 3/5
    //-------------
    FrameBufferCube(const FrameBufferCube &) = delete;

    FrameBufferCube &operator=(const FrameBufferCube &) = delete;

    ~FrameBufferCube() { this->clear(); }

    FrameBufferCube(FrameBufferCube &&other) noexcept;

    FrameBufferCube &operator=(FrameBufferCube &&other) noexcept;

    void bind() override;

    void unbind() override;

};

#endif //PABLO_RENDERER_FRAMEBUFFERCUBE_H
