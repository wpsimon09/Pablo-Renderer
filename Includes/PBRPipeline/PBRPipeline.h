//
// Created by wpsimon09 on 24/12/23.
//

#ifndef CLIONTEST_PBRPIPELINE_H
#define CLIONTEST_PBRPIPELINE_H

#include "FrameBuffer/FrameBuffer.h"
#include "Texture/Texture.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class PBRPipeline {
private:
    FrameBuffer* frameBuffer;

    Texture *hdrCubeMap;
    Texture *prefilterMap;
public:
    unsigned int getHdrCubeMap() const;

    unsigned int getPrefilterMap() const;

    unsigned int getIrradiancaMap() const;

    unsigned int getBrdfLutTexture() const;

private:
    Texture *irradiancaMap;
    Texture *brdfLutTexture;

    unsigned int HDRTexture;
public:
    PBRPipeline(unsigned int hdrTexture);

    void generateHdrCubeMap(Shader shader, unsigned int VA0);
    void generatePrefilterMap(Shader shader, unsigned int VAO);
    void generateIrradianceMap(Shader shader, unsigned int VAO);
    void generateBrdfLutTexture(Shader shader, unsigned int VAO);
};


#endif //CLIONTEST_PBRPIPELINE_H
