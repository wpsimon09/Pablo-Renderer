//
// Created by wpsimon09 on 26/03/24.
//

#include "RenderGraph.h"

RenderGraph::RenderGraph(std::shared_ptr<Scene> scene, std::shared_ptr<OGLRenderer> renderer) {
    this->scene = std::move(scene);
    this->renderer = std::move(renderer);
}

void RenderGraph::execute() {
    auto renderNode = this->renderNodes.begin();
    while(renderNode != this->renderNodes.end()){
        renderNode->second->execute();
    }
}

void RenderGraph::display() {

}

void RenderGraph::addNode(std::shared_ptr<RenderNode> renderNode, std::string name) {

}

