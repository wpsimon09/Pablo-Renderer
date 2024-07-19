//
// Created by wpsimon09 on 12/05/24.
//

#include "PostProcessingRenderer.h"

#include "Renderer/PabloRenderer.h"



void PostProcessingRenderer::setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) {
    this->renderPassInputs = std::move(inputs);
}

void PostProcessingRenderer::renderSceneGraph(SceneNode &sceneNode) {
    //Renderer::renderSceneGraph(sceneNode);
}

void PostProcessingRenderer::render(std::unique_ptr<FrameBuffer> &frameBuffer) {
    frameBuffer->bind();
    glViewport(0,0, frameBuffer->getWidht(), frameBuffer->getHeihgt());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

    auto shader = frameBuffer->getShader();
    shader->use();


    int textureCount = 0;
    for(auto &input: this->renderPassInputs){
        input->setSamplerID(textureCount);
        ShaderHelper::setTextureToShader(shader, *input, input->shaderName);
        textureCount++;
    }
    frameBuffer->renderGeomtry();
}


std::shared_ptr<Texture2D> PostProcessingRenderer::blur(std::shared_ptr<Texture2D> textureToBlur, int intensity) {
    bool horizontal = true, firstIteration = true;

   // pingPongFrameBuffers[0].setColorAttachment(textureToBlur);
    //pingPongFrameBuffers[1].setColorAttachment(textureToBlur);

    auto shader = ShaderManager::getShader(SHADER_BLUR_ANYTHING);
    shader->use();

    for (int i = 0; i < intensity; i++)
    {
        pingPongFrameBuffers[horizontal].bind();
        glViewport(0,0, pingPongFrameBuffers[horizontal].getWidht(), pingPongFrameBuffers[horizontal].getHeihgt());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

        shader->setInt("horizontal", horizontal);

        //use the bright color buffer as a texture for first iteration than swap them
        //set the texture of the frame buffer to be the previous one if its the first itteration we want it to first color buffer of the main FBO
        ShaderHelper::setTextureToShader(shader, firstIteration ? *textureToBlur: *pingPongFrameBuffers[!horizontal].getRenderedResult(), "imageToBlur");

        pingPongFrameBuffers[horizontal].renderGeomtry();

        horizontal = !horizontal;
        if (firstIteration)
        {
            firstIteration = false;
        }
    }

    return pingPongFrameBuffers[!horizontal].getRenderedResult();
}

std::shared_ptr<Texture2D> PostProcessingRenderer::blurToMipMaps(std::shared_ptr<Texture2D> textureToConvolve,
    int mipNumbers) {
    bool horizontal = true, firstIteration = true;




    //coppy the results of the itteration to tthe mip of the image texture provided which should have generated mip maps
    //or just render to quad and stor the result to the mip level of the quead however this would require to create a new shader, one that can store to the mip chain of the image
    return pingPongFrameBuffers[!horizontal].getRenderedResult();

}
