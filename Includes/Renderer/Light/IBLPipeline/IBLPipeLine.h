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
    std::unique_ptr<Texture3D> envMap;
private:
    std::unique_ptr<TextureHDRi> hdriTexture;

    std::unique_ptr<HDRToCubeMap> hdrToCubeMap;


};


#endif //PABLO_RENDERER_IBLPIPELINE_H
