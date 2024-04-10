//
// Created by wpsimon09 on 26/03/24.
//

#ifndef PABLO_RENDERER_RENDERGRAPH_H
#define PABLO_RENDERER_RENDERGRAPH_H

#include "memory"
#include "RenderNode/RenderNode.h"
#include "map"

class RenderGraph {
public:
    RenderGraph(std::shared_ptr<Scene> scene, std::shared_ptr<OGLRenderer> renderer);

    void execute();

    void display();

    void addNode(std::shared_ptr<RenderNode> renderNode, std::string name);

private:
    std::map<std::string, std::shared_ptr<RenderNode>> renderNodes;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<OGLRenderer> renderer;
};


#endif //PABLO_RENDERER_RENDERGRAPH_H
