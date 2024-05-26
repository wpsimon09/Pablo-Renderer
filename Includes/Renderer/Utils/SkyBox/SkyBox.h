
//
// Created by wpsimon09 on 26/05/24.
//

#ifndef PABLO_RENDERER_SKYBOX_H
#define PABLO_RENDERER_SKYBOX_H

#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Material/SkyBoxMaterial/SkyBoxMaterial.h"

class SkyBox:public Renderable {
public:
    SkyBox(std::shared_ptr<TextureBase> skyBox, std::string shaderName);
    bool isVisible = true;
    void setSkyBoxTexture(std::shared_ptr<TextureBase> newTexture);

    void renderUI();

    void render() override;

private:
    std::string skyBoxUniformName;
    std::shared_ptr<Texture3D> skyBoxTexture;
};

#endif //PABLO_RENDERER_SKYBOX_H
