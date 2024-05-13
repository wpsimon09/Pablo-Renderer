//
// Created by wpsimon09 on 12/05/24.
//

#ifndef PABLO_RENDERER_CHROMATICABERRATION_H
#define PABLO_RENDERER_CHROMATICABERRATION_H

#include "Renderer/RenderPass/RenderPass.h"

class ChromaticAberration:public RenderPass {

public:
    ChromaticAberration();
    std::shared_ptr<Texture2D> render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) override;
};


#endif //PABLO_RENDERER_CHROMATICABERRATION_H
