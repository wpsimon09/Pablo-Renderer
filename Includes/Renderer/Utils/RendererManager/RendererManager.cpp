//
// Created by wpsimon09 on 05/04/24.
//

#include "RendererManager.h"

RendererManager::RendererManager() {
    this->renderers.push_back(std::make_shared<OGLRenderer>());
    this->renderers.push_back(std::make_shared<DepthRenderer>());
    this->renderers.push_back(std::make_shared<PostProcessingRenderer>());
}

std::shared_ptr<Renderer> RendererManager::requestRenderer(RENDERER_TYPE type) {
    for(auto& renderer: renderers){
        if(renderer->type == type){
            return renderer;
        }
    }
}

