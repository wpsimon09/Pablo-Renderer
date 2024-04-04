//
// Created by wpsimon09 on 04/04/24.
//

#include "DepthRenderer.h"

void DepthRenderer::render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer) {

}

void DepthRenderer::renderSceneGraph(SceneNode &sceneNode) {
    auto& renderalbe = sceneNode.getRenderable();

    //make shader that only takes position matricies and writes nothing to the color buffer as it is redundatn
}