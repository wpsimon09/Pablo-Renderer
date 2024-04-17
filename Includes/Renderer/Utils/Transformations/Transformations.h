//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_TRANSFORMATIONS_H
#define CLIONTEST_TRANSFORMATIONS_H
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"

class Transformations {
private:
    glm::vec3 position;
    glm::vec3 rotations;
    glm::vec3 scale;

    glm::mat4 m_modelMatrix;

    bool isDirty = true;

    glm::mat4 computeLocalModelMatrix();
public:
    Transformations();
    Transformations(glm::vec3 position, glm::vec3 scale, glm::vec3 rotations);

    void computeModelMatrix();
    void computeModelMatrix(const glm::mat4 &parentGlobalMatrix);

    virtual ~Transformations()=default;

    const glm::vec3 &getPosition() const;
    void setPosition(const glm::vec3 &position);
    void setPosition(float x, float y, float z);

    const glm::vec3 &getRotations() const;
    void setRotations(const glm::vec3 &rotations);
    void setRotations(float x, float y, float z);

    const glm::vec3 &getScale() const;
    void setScale(const glm::vec3 &scale);
    void setScale(float x, float y, float z);

    bool hasChanged() {return this->isDirty;}

    const glm::mat4 &getModelMatrix() const {return this->m_modelMatrix;}



};


#endif //CLIONTEST_TRANSFORMATIONS_H
