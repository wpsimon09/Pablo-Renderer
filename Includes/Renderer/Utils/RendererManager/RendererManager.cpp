//
// Created by wpsimon09 on 05/04/24.
//

#include "RendererManager.h"

RendererManager::RendererManager() {
    this->renderers.push_back(std::make_shared<OGLRenderer>());

    //TODO create class that will be inhereted by all of the renderers in orhter to support polymorphism
}

std::shared_ptr<Renderer> RendererManager::requestRenderer(RENDERER_TYPE type) {
    for(auto& renderer: renderers){

        if(renderer->type == type){
            return renderer;
        }
    }
}

