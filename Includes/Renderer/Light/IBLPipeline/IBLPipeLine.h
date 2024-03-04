//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_IBLPIPELINE_H
#define PABLO_RENDERER_IBLPIPELINE_H

#include "Renderer/Light/IBLPipeline/Stages/HDRToCubeMap/HDRToCubeMap.h"
#include "Renderer/Light/IBLPipeline/Stages/Irradiance/Irradiance.h"
#include "Renderer/Light/IBLPipeline/Stages/PrefilterMap/PrefilterMap.h"
#include "Renderer/Light/IBLPipeline/Stages/BRDF/BRDF.h"


class IBLPipeLine {
public:
    explicit IBLPipeLine(const char* path);
    void generateIBLTextures();

    //-------------------
    // GENERATED TEXTURES
    //-------------------
    std::shared_ptr<Texture3D> envMap;

    std::vector<std::shared_ptr<TextureBase>> iblTextures;

    std::shared_ptr<Texture3D> irradianceMap;
    std::shared_ptr<Texture3D> prefilterMap;
    std::shared_ptr<Texture2D> BRDFLutTexture;
private:

    std::shared_ptr<TextureHDRi> inputHDRI;

    std::shared_ptr<PrefilterMap> hdrToPrefilterMap;
    std::unique_ptr<HDRToCubeMap> hdrToCubeMap;
    std::unique_ptr<Irradiance> hdrToIrradiance;
    std::shared_ptr<BRDF> brdfStage;
};


#endif //PABLO_RENDERER_IBLPIPELINE_H
