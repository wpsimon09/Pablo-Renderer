//
// Created by wpsimon09 on 29/12/23.
//

#include "PostProcessing.h"


void PostProcessing::draw(Shader shader, unsigned int VAO) {

}

unsigned int PostProcessing::getTextureID() {
    return 0;
}

Texture *PostProcessing::getTexture() {
    return nullptr;
}

PostProcessing::PostProcessing() {
    this->frameBuffer = new FrameBuffer();
    this->drawnScene = new Texture(GL_TEXTURE_2D, "finalFrameBuffer", glm::vec2(800,600), GL_RGBA );
    this->frameBuffer->mountTexture(this->drawnScene);
    this->frameBuffer->updateRenderBufferStorage(this->frameBuffer->texture->getDimentions());
}

PostProcessing::PostProcessing(Texture *texture, FrameBuffer *FBO) {

}
