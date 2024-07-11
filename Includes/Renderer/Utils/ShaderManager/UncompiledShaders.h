//
// Created by wpsimon09 on 17/05/24.
//

#ifndef PABLO_RENDERER_UNCOMPILEDSHADERS_H
#define PABLO_RENDERER_UNCOMPILEDSHADERS_H

#include "iostream"
#include "Renderer/Enums/ShaderTypes.h"
#include "vector"

struct UncompiledShader {
    std::string vertexPath;
    std::string fragmentPath;
    std::string name;
    ShaderType type;

    UncompiledShader(ShaderType type, std::string vertexP, std::string fragmentP, std::string name) {
        this->vertexPath = std::move(vertexP);
        this->fragmentPath = std::move(fragmentP);
        this->name = std::move(name);
        this->type = type;
    }
};

const std::vector<UncompiledShader> __uncompiledShaders = {
        UncompiledShader(SHADER_HDR_2_CUBE_MAP, "VertexShader/PBR/HDRtoCubeMapVertex.glsl",
                         "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "HDR TO CUBE MAP"),

        UncompiledShader(SHADER_GENERATE_IRRADIANCE, "VertexShader/PBR/HDRtoCubeMapVertex.glsl",
                         "FragmentShader/PBR/EnviromentToIrradianceFragment.glsl", "CUBE MAP TO IRRADIANCE"),

        UncompiledShader(SHADER_GENERATE_PREFILTER, "VertexShader/PBR/HDRtoCubeMapVertex.glsl",
                         "FragmentShader/PBR/PrefilteringHDRFragment.glsl", "CUBE MAP TO PREFILTER"),

        UncompiledShader(SHADER_GENERATE_BRDF_LUT, "VertexShader/PBR/LutTextureVertex.glsl",
                         "FragmentShader/PBR/BRDFLutFragment.glsl", "LUT_Textue map"),

        UncompiledShader(SHADER_SKY_BOX, "VertexShader/PBR/SkyBoxVertex.glsl", "FragmentShader/PBR/SkyBoxFragment.glsl",
                         "SKY BOX SHADER"),

        UncompiledShader(SHADER_AREA_LIGHT_COLOUR, "VertexShader/PBR/PBRVertex-Simple.glsl",
                         "FragmentShader/PBR/AreaLightFragemnt/AreaLight.frag", "AREA LIGHT COLOUR"),

        UncompiledShader(SHADER_AREA_LIGHT_TEXTURES, "VertexShader/PBR/PBRVertex.glsl",
                         "FragmentShader/PBR/AreaLightFragemnt/AreaLightTextured.frag", "AREA LIGHT TEXTURED"),

        UncompiledShader(SHADER_AREA_LIGHT_SOURCE, "VertexShader/AreaLightSourceVertex.glsl",
                         "FragmentShader/AreaLightSourceFragment.glsl", "AREA LIGHT SOURCE"),

        UncompiledShader(SHADER_PBR_COLOUR, "VertexShader/PBR/PBRVertex-Simple.glsl",
                         "FragmentShader/PBR/PBRFragment-IBL-Color.glsl", "PBR COLOUR"),

        UncompiledShader(SHADER_PBR_TEXTURED, "VertexShader/PBR/PBRVertex.glsl",
                         "FragmentShader/PBR/PBR-IBL-Textured-Fragment.glsl", "PBR TEXTURED"),

        UncompiledShader(SHADER_DIRECTIONAL_LIGHT_SOURCE, "VertexShader/AdvancedLightning/LightSourceVertex.glsl",
                         "FragmentShader/AdvancedLightning/LightSourceFragment.glsl",
                         "DIRECTIONAL LIGHT SOURCE SHADER"),

        UncompiledShader(SHADER_SHADOW_MAP, "VertexShader/ShadowMap/ShadowMapVertex.glsl",
                         "FragmentShader/ShadowMap/ShadowMapFragment.glsl", "SHADOW MAP PASS"),

        UncompiledShader(SHADER_FRAME_BUFFER, "VertexShader/FrameBufferDebugVertex.glsl",
                         "FragmentShader/FrameBufferDebugFragment.glsl", "DRAW TO FRAME BUFFER SHADER"),

        UncompiledShader(SHADER_SMALL_FRAME_BUFFER, "VertexShader/FrameBufferDebugVertex.glsl",
                         "FragmentShader/Debug/FrameBufferDebug2.glsl", "Small freme buffer shader"),

        UncompiledShader(SHADER_CHROMATIC_ABBERATION, "VertexShader/FrameBufferDebugVertex.glsl",
                         "FragmentShader/Postprocessing/ChromaticAbriviationFragment.glsl",
                         "CHROMATIC ABBERATION SHADER"),

        UncompiledShader(SHADER_PIXELATION, "VertexShader/FrameBufferDebugVertex.glsl",
                         "FragmentShader/Postprocessing/PixelationAndChromaticAbriviationFragment.glsl",
                         "PIXELATION SHADER"),

        UncompiledShader(SHADER_POST_PROCESSING_MERGER, "VertexShader/FrameBufferDebugVertex.glsl",
                         "FragmentShader/Postprocessing/PostProcessMerger.frag", "SHADER MERGER"),

        UncompiledShader(SHADER_GRID, "VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl",
                         "SHADER GRID"),

        UncompiledShader(SHADER_PIXEL_PICKING, "VertexShader/PixelPickingVertex/PixelPickingVertex.vert",
                         "FragmentShader/PixelPicking/PixelPicking.frag",
                         "PIXEL PICKING SHADER"),

    UncompiledShader(SHADER_SCREEN_SPACE_REFLECTIONS, "VertexShader/GlobalIllumination/SSRVertex.vert",
             "FragmentShader/GlobalIllumination/SSRMcGuire.frag",
             "SSR UV SHADER"),

    UncompiledShader(SHADER_SCREEN_SPACE_REFLECTIONS_COLOUR_SAMPLING, "VertexShader/GlobalIllumination/SSRVertex.vert",
         "FragmentShader/GlobalIllumination/SSRMerge.frag",
         "REFLECTED COLOUR"),
};

#endif //PABLO_RENDERER_UNCOMPILEDSHADERS_H
