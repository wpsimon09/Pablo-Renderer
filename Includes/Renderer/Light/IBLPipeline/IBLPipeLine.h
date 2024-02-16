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

    //-------------------
    // GENERATED TEXTURES
    //-------------------
    Texture3D envMap;
private:
    TextureHDRi hdriTexture;

    HDRToCubeMap* hdrToCubeMap;


};


#endif //PABLO_RENDERER_IBLPIPELINE_H
