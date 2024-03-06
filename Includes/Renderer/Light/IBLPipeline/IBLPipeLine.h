//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_IBLPIPELINE_H
#define PABLO_RENDERER_IBLPIPELINE_H

#include "Renderer/Light/IBLPipeline/Stages/HDRToCubeMap/HDRToCubeMap.h"
#include "Renderer/Light/IBLPipeline/Stages/Irradiance/Irradiance.h"
#include "Renderer/Light/IBLPipeline/Stages/PrefilterMap/PrefilterMap.h"
#include "Renderer/Light/IBLPipeline/Stages/BRDF/BRDF.h"
#include "Renderer/Material/Material.h"

class IBLPipeLine {
public:
    explicit IBLPipeLine(const char* path);
    void generateIBLTextures();
    void configureShader(std::shared_ptr<Shader> shader, int maximalSamplerCount);

    std::shared_ptr<Texture3D> envMap;

    //-------------------
    // GENERATED TEXTURES
    //-------------------
    //vector of shared pointers of PBR Material struct with texture and shader name
    // bit confusing but it iss what it iss
    std::vector<std::shared_ptr<PBRMaterial<TextureBase>>> iblTextures;
private:
    std::shared_ptr<TextureHDRi> inputHDRI;

    std::unique_ptr<PrefilterMap> hdrToPrefilterMap;
    std::unique_ptr<HDRToCubeMap> hdrToCubeMap;
    std::unique_ptr<Irradiance> hdrToIrradiance;
    std::shared_ptr<BRDF> brdfStage;
};


#endif //PABLO_RENDERER_IBLPIPELINE_H
