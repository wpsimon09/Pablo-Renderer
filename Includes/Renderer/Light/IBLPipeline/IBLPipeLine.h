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

/***
 * Class responsible for executing splits sum approximation based on the provided HDRi equirectangular map of the environment
 */
class IBLPipeLine {
public:
    /***
     * Creates instance of the IBL pipeline
     * @param path path to the equirectangular map of the environment
     */
    explicit IBLPipeLine(const char* path);

    /***
     * @brief Regenerates the IBL
     * @param path
     */
    void recalculateIBL(const char* path);

    /***
     * Generates and stores the generated textures inside vector
     */
    void generateIBLTextures();

    /**
     * Pass the generated textures to the provided shader
     * @param shader shader that has ability to render IBL
     * @param maximalSamplerCount number indicating which is the last used texture sampler eg.: albedo (0), normal(1), max sampler is hence 1
     */
    void configureShader(std::shared_ptr<Shader> shader, int maximalSamplerCount);

    /***
     * Cube map texture of the equirectangualr map
     */
    std::shared_ptr<TextureBase> envMap;

    /***
     * Generated IBL textures
     */
    std::vector<std::shared_ptr<PBRMaterial<TextureBase>>> iblTextures;

    int getSamplersCount() {return this->samplersCount; }
private:
    std::shared_ptr<TextureHDRi> inputHDRI;
    int samplersCount;
    //---------------------------
    // STAGES OF THE IBL PIPELINE
    //---------------------------
    std::vector<std::unique_ptr<BaseStage>> stages;

    std::unique_ptr<PrefilterMap> hdrToPrefilterMap;
    std::unique_ptr<HDRToCubeMap> hdrToCubeMap;
    std::unique_ptr<Irradiance> hdrToIrradiance;
    std::shared_ptr<BRDF> brdfStage;
};


#endif //PABLO_RENDERER_IBLPIPELINE_H
