//
// Created by wpsimon09 on 06/01/24.
//

#ifndef PABLO_RENDERER_LIGHT_H
#define PABLO_RENDERER_LIGHT_H

#include "iostream"
#include "glm/glm.hpp"

template<typename T>
struct LightProperty{
    T property;
    std::string uniformName;
    LightProperty(T property, std::string unifrom){
        this->property = property;
        this->uniformName = unifrom;
    }
};

class Light {
public:
    Light(glm::vec3 position, glm::vec3 color);
protected:
    LightProperty<glm::vec3>* position;
    LightProperty<glm::vec3 >* color;

};


#endif //PABLO_RENDERER_LIGHT_H
