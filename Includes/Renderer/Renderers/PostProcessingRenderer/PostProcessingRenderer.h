//
// Created by wpsimon09 on 12/05/24.
//

#ifndef PABLO_RENDERER_POSTPROCESSINGRENDERER_H
#define PABLO_RENDERER_POSTPROCESSINGRENDERER_H

#include "Renderer/Renderers/Renderer.h"

class PostProcessingRenderer: public Renderer{
public:
    PostProcessingRenderer():Renderer(),
    pingPongFrameBuffers{FrameBuffer(1920,1080),FrameBuffer(1920,1080)},
    convolutionFrameBuffer(1920, 1080, nullptr, nullptr, true, 10)
    {
        this->type = POST_PROCESSING;
    }

    void setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) override;

    void render(std::unique_ptr<FrameBuffer> &frameBuffer) override;

    std::shared_ptr<Texture2D> blurToMipMaps(std::shared_ptr<Texture2D> textureToConvolve, int mipNumbers) override;

    std::shared_ptr<Texture2D> blur(std::shared_ptr<Texture2D> textureToBlur,int intensity = 0) override;
protected:
    void renderSceneGraph(SceneNode &sceneNode) override;
private:
    FrameBuffer pingPongFrameBuffers[2];
    FrameBuffer convolutionFrameBuffer;
};


#endif //PABLO_RENDERER_POSTPROCESSINGRENDERER_H
