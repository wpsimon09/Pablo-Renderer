//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_IBLPIPELINE_H
#define PABLO_RENDERER_IBLPIPELINE_H

#include "Renderer/Light/IBLPipeline/Stages/HDRToCubeMap/HDRToCubeMap.h"

class IBLPipeLine {
public:
    explicit IBLPipeLine(const char* path);
    void generateIBLTextures();
private:
    TextureHDRi hdriTexture;

    HDRToCubeMap* hdrToCubeMap;
    TextureBase envMap;


};


#endif //PABLO_RENDERER_IBLPIPELINE_H
