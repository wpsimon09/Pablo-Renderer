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

        POST_PROCESSING_CHROMATIC_ABERRATION = 3,
        POST_PROCESSING_PIXELATION = 4,

        FINAL_PASS = 2,

};

#endif //PABLO_RENDERER_RENDERPASSTYPES_H
