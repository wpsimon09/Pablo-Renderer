//
// Created by wpsimon09 on 05/04/24.
//

#include "RendererManager.h"

RendererManager::RendererManager() {
    RendererManager::renderers.push_back(std::make_shared<OGLRenderer>());
    RendererManager::renderers.push_back(std::make_shared<DepthRenderer>());
}

std::shared_ptr<OGLRenderer> RendererManager::requestRenderer(RENDERER_TYPE type) {
    for(auto& renderer: renderers){
        if(renderer->rendererType == type){
            return renderer;
        }
    }
}

