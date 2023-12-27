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
    this->prefilterMap = new Texture(GL_TEXTURE_CUBE_MAP,  "prefilterMap", glm::vec2(128, 128),GL_RGB);
    this->brdfLutTexture = new Texture(GL_TEXTURE_2D, "brdfLutTexture", glm::vec2(512, 512),GL_RG);

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
    this->frameBuffer->texture->generateMipmap();
    std::cout<<"Created hdr texture: "<<this->hdrCubeMap->ID<<std::endl;
    std::cout<<std::endl;
    this->frameBuffer->cancel();
}

void PBRPipeline::generateIrradianceMap(Shader shader,unsigned int envMap, unsigned int VAO) {
    shader.use();
    shader.setInt("envMap", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envMap);
    this->frameBuffer->mountTexture(irradiancaMap);
    this->frameBuffer->texture->changeFilteringMethod(GL_LINEAR, GL_LINEAR);
    glViewport(0,0, this->irradiancaMap->getDimentions().x, this->irradiancaMap->getDimentions().y);
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

    std::cout<<"Created irradiance texture: "<<this->irradiancaMap->ID<<std::endl;
    this->frameBuffer->cancel();
}

void PBRPipeline::generatePrefilterMap(Shader shader,unsigned int envMap, unsigned int VAO) {
    shader.use();
    shader.setInt("envMap", 2);
    this->frameBuffer->mountTexture(this->prefilterMap);
    this->frameBuffer->texture->generateMipmap();

    //bind the texture after all of the operations
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envMap);
    const unsigned int maxMipMapLevels = 5;
    this->frameBuffer->use();

    std::cout<<"Drawing prefilter texture to the frame buffer with name: "<<frameBuffer->name<<"and ID: "<<frameBuffer->ID<<std::endl;

    //loop for each rougness
    for (unsigned int mip = 0; mip <maxMipMapLevels; ++mip) {
        const auto mipMapWidth = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        const auto mipMapHeihgt = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        this->frameBuffer->updateRenderBufferStorage(glm::vec2(mipMapWidth, mipMapHeihgt));
        glViewport(0,0, mipMapWidth, mipMapHeihgt);
        this->frameBuffer->use();
        float roughness = (float)mip / (float)(maxMipMapLevels - 1);
        shader.setFloat("roughness", roughness);

        for (int i = 0; i < 6; ++i) {
            this->frameBuffer->useTexture(this->prefilterMap, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, mip);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            std::cout<<"Drawing mip map at level"<<mip<<" for roughness level"<<roughness<<std::endl;
            shader.use();
            glBindVertexArray(VAO);
            shader.setMat4("view", captureViews[i]);
            shader.setMat4("projection", captureProjection);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
    }
    std::cout<<"Created prefiltered texture: "<<this->prefilterMap->ID<<std::endl;
    this->frameBuffer->cancel();
}


void PBRPipeline::generateBrdfLutTexture(Shader shader, unsigned int VAO) {
    this->frameBuffer->mountTexture(brdfLutTexture);
    this->frameBuffer->updateRenderBufferStorage(this->frameBuffer->texture->getDimentions());
    this->frameBuffer->useTexture(this->brdfLutTexture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D);
    this->frameBuffer->use();
    glViewport(0,0, this->frameBuffer->texture->getDimentions().x, this->frameBuffer->texture->getDimentions().y);
    shader.use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAO);
    shader.setMat4("projection", captureProjection);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    this->frameBuffer->cancel();
}

unsigned int PBRPipeline::getHdrCubeMap() const {
    return this->hdrCubeMap->ID;
}

unsigned int PBRPipeline::getPrefilterMap() const {
    return this->prefilterMap->ID;
}

unsigned int PBRPipeline::getIrradiancaMap() const {
    return this->irradiancaMap->ID;
}

unsigned int PBRPipeline::getBrdfLutTexture() const {
    return brdfLutTexture->ID;
}
