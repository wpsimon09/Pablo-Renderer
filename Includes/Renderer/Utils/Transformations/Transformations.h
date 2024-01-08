//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_TRANSFORMATIONS_H
#define CLIONTEST_TRANSFORMATIONS_H
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Transformations {
private:
    glm::vec3 position;
    glm::vec3 rotations;
    glm::vec3 scale;
public:
    Transformations();
    Transformations(glm::vec3 position, glm::vec3 scale, glm::vec3 rotations);
    glm::mat4 generateModelMatrix();

    virtual ~Transformations()=default;

    const glm::vec3 &getPosition() const;
    void setPosition(const glm::vec3 &position);
    const glm::vec3 &getRotations() const;
    void setRotations(const glm::vec3 &rotations);
    const glm::vec3 &getScale() const;
    void setScale(const glm::vec3 &scale);
};


#endif //CLIONTEST_TRANSFORMATIONS_H
