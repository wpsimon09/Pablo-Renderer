//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_PBRCOLOR_H
#define PABLO_RENDERER_PBRCOLOR_H

#include "Renderer/Material/Material.h"

class PBRColor: public Material {
public:
    PBRColor();
    PBRColor(glm::vec3 albedo, float metallic , float rougness, float ao);
private:
    PBRMaterial<glm::vec3>* albedo;
    PBRMaterial<float>* metalness;
    PBRMaterial<float>* rougness ;
    PBRMaterial<float>* ao;
public:
    PBRMaterial<glm::vec3> *getAlbedo() const;

    PBRMaterial<float> *getMetalness() const;

    PBRMaterial<float> *getRougness() const;

    PBRMaterial<float> *getAo() const;

    friend std::ostream& operator<<(std::ostream& os, const PBRColor& mat);

    void printLog() const override;
};


#endif //PABLO_RENDERER_PBRCOLOR_H
