//
// Created by wpsimon09 on 03/07/24.
//

#ifndef SCREENSPACEREFLECTION_H
#define SCREENSPACEREFLECTION_H
#include "Renderer/RenderPass/RenderPass.h"
#include "Renderer/Utils/Parameters/Parameter.h"

class ScreenSpaceReflection: public RenderPass {
public:
    ScreenSpaceReflection();

    std::shared_ptr<Texture2D>
    render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) override;
private:
    std::unique_ptr<FrameBuffer> mergeFrameBufer;
    std::map<std::string, Parameter> uniformValues;


    void setParamsToShader(std::shared_ptr<Shader> shader);

public:
    void renderUI() override;
};



#endif //SCREENSPACEREFLECTION_H
