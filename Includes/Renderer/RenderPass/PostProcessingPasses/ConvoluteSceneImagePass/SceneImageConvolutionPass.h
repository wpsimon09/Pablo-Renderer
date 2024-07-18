//
// Created by wpsimon09 on 18/07/24.
//

#ifndef SCENEIMAGECONVOLUTION_H
#define SCENEIMAGECONVOLUTION_H

#include "Renderer/RenderPass/RenderPass.h"

class SceneImageConvolutionPass:public RenderPass {
public:
    SceneImageConvolutionPass();

    std::shared_ptr<Texture2D>
    render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) override;

    void renderUI() override;
};



#endif //SCENEIMAGECONVOLUTION_H
