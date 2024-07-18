//
// Created by wpsimon09 on 30/04/24.
//

#ifndef PABLO_RENDERER_RENDERPASSTYPES_H
#define PABLO_RENDERER_RENDERPASSTYPES_H

/***
 * Render passes implemented in application this can fetched via RenderGraph class
 */
enum RENDER_PASS {
        SHADOW_MAP_PASS = 0,
        SCENE_PASS =1,

        POST_PROCESSING_PASS = 2,

        FINAL_PASS = 3,

        PIXEL_PICKING_PASS = 4,

        PIXELATION_POST_PROCESSING_PASS = 5,
        CHROMATIC_ABBERATION_POST_PROCESSING_PASS = 6,
        SCREEN_SPACE_REFLECTION_PASS = 7,
        SCENE_CONVOLUTION_PASS = 7,
};

#endif //PABLO_RENDERER_RENDERPASSTYPES_H
