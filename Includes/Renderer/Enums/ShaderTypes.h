//
// Created by wpsimon09 on 17/05/24.
//

#ifndef PABLO_RENDERER_SHADERTYPES_H
#define PABLO_RENDERER_SHADERTYPES_H

enum ShaderType {
    SHADER_HDR_2_CUBE_MAP = 0,
    SHADER_GENERATE_IRRADIANCE = 1,
    SHADER_GENERATE_PREFILTER = 2,
    SHADER_GENERATE_BRDF_LUT = 3,

    SHADER_SKY_BOX = 4,

    SHADER_AREA_LIGHT_COLOUR = 5,
    SHADER_AREA_LIGHT_TEXTURES = 6,

    SHADER_PBR_COLOUR = 7,
    SHADER_PBR_TEXTURED = 8,

    SHADER_SHADOW_MAP = 9,

    SHADER_FRAME_BUFFER = 10,

    SHADER_CHROMATIC_ABBERATION = 11,
    SHADER_PIXELATION = 12,

    SHADER_AREA_LIGHT_SOURCE = 13,
    SHADER_DIRECTIONAL_LIGHT_SOURCE = 14,

    SHADER_GRID = 15,

    SHADER_SMALL_FRAME_BUFFER = 16,

    SHADER_POST_PROCESSING_MERGER = 17,

    SHADER_PIXEL_PICKING = 18,

    SHADER_SCREEN_SPACE_REFLECTIONS = 19,
    SHADER_SCREEN_SPACE_REFLECTIONS_COLOUR_SAMPLING = 20,
    SHADER_SCREEN_SPACE_REFLECTIONS_BLURRING = 21,
    SHADER_SCREEN_SPACE_REFLECTIONS_COMBINE = 22,

    SHADER_BLUR_ANYTHING = 23,
    SHADER_BLUR_HORIZONTAL = 24,
    SHADER_BLUR_VERTICAL = 25,
};


#endif //PABLO_RENDERER_SHADERTYPES_H
