//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_PBRTEXTURED_H
#define PABLO_RENDERER_PBRTEXTURED_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D.h"
#include "iostream"
#include "ostream"
class PBRTextured : public Material{
public:
    // ASSUMPTION WARNING
    // assumption here is made that within the directory materials follow the following naming convention
    // the path parameter should be passed as
    // Assets/Textures/directory
    // albedo.png/jpg, metallic.png/jpg, rougness.png/jpg
    explicit PBRTextured(std::string pathToTheDirectory,  std::string shaderNamingConvention = "_map", std::string fileFormat = ".png");

    PBRMaterial<Texture2D> *getBaseColor() const;

    PBRMaterial<Texture2D> *getNormalMap() const;

    PBRMaterial<Texture2D> *getRoughness() const;

    PBRMaterial<Texture2D> *getMetalness() const;

    PBRMaterial<Texture2D> *getAo() const;

    friend std::ostream& operator<<(std::ostream& os, const PBRTextured& mat);

    void printLog() const override;

private:
    PBRMaterial<Texture2D>* baseColor;
    PBRMaterial<Texture2D>* normalMap;
    PBRMaterial<Texture2D>* roughness;
    PBRMaterial<Texture2D>* metalness;
    PBRMaterial<Texture2D>* ao;
};


#endif //PABLO_RENDERER_PBRTEXTURED_H
