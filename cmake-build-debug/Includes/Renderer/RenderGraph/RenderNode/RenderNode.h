//
// Created by wpsimon09 on 28/03/24.
//

#ifndef PABLO_RENDERER_RENDERNODE_H
#define PABLO_RENDERER_RENDERNODE_H

#include "Renderer/RenderGraph/RenderPass/RenderPass.h"

class RenderNode {
public:
    RenderNode(std::shared_ptr<RenderPass> renderPass = nullptr);

    void addInput(std::shared_ptr<TextureBase> input);

    void addOutput(std::shared_ptr<TextureBase> output);

    void execute();
private:
    std::shared_ptr<RenderNode> parent;
    std::shared_ptr<RenderPass> renderPass;
    std::vector<std::shared_ptr<TextureBase>> inputs;
    std::vector<std::shared_ptr<TextureBase>> outputs;
};


#endif //PABLO_RENDERER_RENDERNODE_H
