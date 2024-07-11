//
// Created by wpsimon09 on 03/07/24.
//

#ifndef SCREENSPACEREFLECTION_H
#define SCREENSPACEREFLECTION_H
#include "Renderer/RenderPass/RenderPass.h"


class ScreenSpaceReflection: public RenderPass {
public:
    ScreenSpaceReflection();

    std::shared_ptr<Texture2D>
    render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) override;
private:
    std::unique_ptr<FrameBuffer> mergeFrameBufer;

    float zThikness = 0.2;
    float nerPlane;
    float farPlane;
    float stride = 0.2;
    float maxSteps = 20;
    float maxDistance = 30;
    float strideZCutoff = 20;
    float fadeStart = 200;
    float fadeEnd = 300;
    float sslrPadding = 0.2;

    void setParamsToShader(std::shared_ptr<Shader> shader);

public:
    void renderUI() override;
};



#endif //SCREENSPACEREFLECTION_H
