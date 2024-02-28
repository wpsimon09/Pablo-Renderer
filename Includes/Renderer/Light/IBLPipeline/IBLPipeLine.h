//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_IBLPIPELINE_H
#define PABLO_RENDERER_IBLPIPELINE_H

#include "Renderer/Light/IBLPipeline/Stages/HDRToCubeMap/HDRToCubeMap.h"
#include "Renderer/Light/IBLPipeline/Stages/Irradiance/Irradiance.h"
#include "Renderer/Light/IBLPipeline/Stages/PrefilterMap/PrefilterMap.h"

class IBLPipeLine {
public:
    explicit IBLPipeLine(const char* path);
    void generateIBLTextures();

    //-------------------
    // GENERATED TEXTURES
    //-------------------
    std::shared_ptr<Texture3D> envMap;
    std::shared_ptr<Texture3D> irradianceMap;
    std::shared_ptr<Texture3D> prefilterMap;

private:
    std::shared_ptr<TextureHDRi> inputHDRI;

    std::shared_ptr<PrefilterMap> hdrToPrefilterMap;
    std::unique_ptr<HDRToCubeMap> hdrToCubeMap;
    std::unique_ptr<Irradiance> hdrToIrradiance;


};


#endif //PABLO_RENDERER_IBLPIPELINE_H
