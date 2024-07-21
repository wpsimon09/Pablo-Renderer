//
// Created by wpsimon09 on 21/07/24.
//

#ifndef CONETRACINGPASS_H
#define CONETRACINGPASS_H

#include "Renderer/RenderPass/RenderPass.h"

class ConeTracingPass: public RenderPass {
public:
    ConeTracingPass();

    void renderUI() override;

    std::shared_ptr<Texture2D> render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) override;
};



#endif //CONETRACINGPASS_H
