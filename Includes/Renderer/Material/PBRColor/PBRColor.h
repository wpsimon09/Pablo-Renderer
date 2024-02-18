//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_PBRCOLOR_H
#define PABLO_RENDERER_PBRCOLOR_H

#include "Renderer/Material/Material.h"
#include "memory"

class PBRColor: public Material {
public:
    explicit PBRColor(Shader* shader, glm::vec3 albedo = glm::vec3(0.4f, 0.4f, 0.4f), float metallic = 0.7f , float rougness = 0.2f, float ao= 0.6f, std::string shaderNamingConvention = "_val");
private:
    std::unique_ptr<PBRMaterial<glm::vec3>> albedo;
    std::unique_ptr<PBRMaterial<float>> metalness;
    std::unique_ptr<PBRMaterial<float>> rougness ;
    std::unique_ptr<PBRMaterial<float>> ao;
public:
    PBRMaterial<glm::vec3> *getAlbedo() const;

    PBRMaterial<float> *getMetalness() const;

    PBRMaterial<float> *getRougness() const;

    PBRMaterial<float> *getAo() const;

    friend std::ostream& operator<<(std::ostream& os, const PBRColor& mat);

    void printLog() const override;

    void configureShader() override;
};


#endif //PABLO_RENDERER_PBRCOLOR_H
