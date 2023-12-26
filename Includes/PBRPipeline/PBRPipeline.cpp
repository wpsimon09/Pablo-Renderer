//
// Created by wpsimon09 on 24/12/23.
//

#include "PBRPipeline.h"


glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
glm::mat4 captureViews[] =
        {
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
        };

PBRPipeline::PBRPipeline(unsigned int hdrTexture) {
    this->HDRTexture = hdrTexture;


    this->hdrCubeMap = new Texture(GL_TEXTURE_CUBE_MAP,  "equirectangularMap", glm::vec2(1980, 1980),GL_RGBA);
    this->irradiancaMap = new Texture(GL_TEXTURE_CUBE_MAP,  "irradianceMap", glm::vec2(32,32),GL_RGBA);
    this->prefilterMap = new Texture(GL_TEXTURE_CUBE_MAP,  "prefilterMap", glm::vec2(520, 520),GL_RGB);
    this->brdfLutTexture = new Texture(GL_TEXTURE_2D, "brdfLutTexture", glm::vec2(520, 520),GL_RG);

    this->frameBuffer = new FrameBuffer();
}

void PBRPipeline::generateHdrCubeMap(Shader shader, unsigned int VAO) {
    //pass the input to the shader
    shader.use();
    shader.setInt("equirectangularMap", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->HDRTexture);
    this->frameBuffer->mountTexture(hdrCubeMap);
    glViewport(0,0, this->frameBuffer->texture->getDimentions().x, this->frameBuffer->texture->getDimentions().y);
    this->frameBuffer->use();
    for (int i = 0; i < 6; ++i)
    {
        std::cout<<"Drawing env texture to the frame buffer with name: "<<frameBuffer->name<<"and ID: "<<frameBuffer->ID<<std::endl;
        frameBuffer->useTexture(this->hdrCubeMap, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X+i);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        glBindVertexArray(VAO);
        shader.setMat4("view", captureViews[i]);
        shader.setMat4("projection", captureProjection);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    std::cout<<"Created hdr texture: "<<this->hdrCubeMap->ID<<std::endl;
    this->frameBuffer->cancel();
}

void PBRPipeline::generateIrradianceMap(Shader shader,unsigned int envMap, unsigned int VAO) {
    shader.use();
    shader.setInt("envMap", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envMap);
    this->irradiancaMap->changeFilteringMethod(GL_LINEAR, GL_LINEAR);
    this->frameBuffer->mountTexture(irradiancaMap);
    glViewport(0,0, 32, 32);
    this->frameBuffer->use();
    for (int i = 0; i < 6; ++i)
    {
        std::cout<<"Drawing irradiance texture to the frame buffer with name: "<<frameBuffer->name<<"and ID: "<<frameBuffer->ID<<std::endl;
        frameBuffer->useTexture(this->irradiancaMap, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X+i);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        glBindVertexArray(VAO);
        shader.setMat4("view", captureViews[i]);
        shader.setMat4("projection", captureProjection);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    std::cout<<"Created irradiance texture: "<<this->irradiancaMap->ID<<std::endl;
    this->frameBuffer->cancel();
}

void PBRPipeline::generatePrefilterMap(Shader shader, unsigned int VAO) {

}


void PBRPipeline::generateBrdfLutTexture(Shader shader, unsigned int VAO) {

}

unsigned int PBRPipeline::getHdrCubeMap() const {
    return this->hdrCubeMap->ID;
}

unsigned int PBRPipeline::getPrefilterMap() const {
    return prefilterMap->ID;
}

unsigned int PBRPipeline::getIrradiancaMap() const {
    return irradiancaMap->ID;
}

unsigned int PBRPipeline::getBrdfLutTexture() const {
    return brdfLutTexture->ID;
}
