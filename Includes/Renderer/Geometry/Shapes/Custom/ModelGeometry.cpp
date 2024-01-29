//
// Created by wpsimon09 on 31/12/23.
//

#include "ModelGeometry.h"

#include <utility>
#include "Model.h"


ModelGeometry::ModelGeometry(std::string name, std::vector<Vertex> verticies,std::vector<unsigned int> indecies): Geometry() {
    this->name = std::move(name);
    this->shapes = GL_TRIANGLES;
    this->vao = new VAO(std::move(verticies), std::move(indecies));
}

ModelGeometry::ModelGeometry(const char *pathToTheModel): Geometry() {
    Model model(pathToTheModel);
    this->shapes = GL_TRIANGLES;
    this->vao = model.parseToRenderable();
}

void ModelGeometry::render() const {
    this->vao->bind();
    glDrawElements(this->shapes, this->vao->getNumberOfIndecies(), GL_UNSIGNED_INT, 0);

    this->vao->unbind();
    glActiveTexture(GL_TEXTURE0);
    glGetError();
}


