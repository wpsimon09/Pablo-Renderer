//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(std::string pathToTheDirectory, std::string shaderNamingConvention, std::string fileFormat): Material() {
    Texture2D albedo((pathToTheDirectory+"/albedo"+ fileFormat).c_str(), true);
    this->baseColor = new PBRMaterial<Texture2D>(albedo, shaderNamingConvention+"Albedo");

    Texture2D rougness((pathToTheDirectory+"/rougness"+ fileFormat).c_str(), true);
    this->roughness = new PBRMaterial<Texture2D>(rougness, shaderNamingConvention+"Rougness");

    Texture2D metallic((pathToTheDirectory+"/metallic"+ fileFormat).c_str(), true);
    this->metalness = new PBRMaterial<Texture2D>(metallic, shaderNamingConvention+"Metallic");

    Texture2D normal((pathToTheDirectory+"/normal"+ fileFormat).c_str(), true);
    this->normalMap = new PBRMaterial<Texture2D>(normal, shaderNamingConvention+"Normal");

    Texture2D _ao((pathToTheDirectory + "/ao" + fileFormat).c_str(), true);
    this->ao = new PBRMaterial<Texture2D>(_ao, shaderNamingConvention + "Ao");

}

std::ostream &operator<<(std::ostream &os, const PBRTextured &mat) {
    os<<"PBR material using TEXTURES has following properties"<<std::endl;
    os<< "BASE COLOR:" << std::endl;
    os<< "FULL PATH: "<< mat.baseColor->type.getFullPath() << std::endl;
    os<<"SHADER NAME: "<<mat.baseColor->shaderName<<std::endl;
    os<< "STATUS:" << std::endl;
    mat.baseColor->type.wasFound ? std::cout<<"\xE2\x9C\x93"<<std::endl : std::cout<<"!!! TEXTURE WAS NOT FOUND !!!"<<std::endl;

    os<<"==================================================="<<std::endl;

    os<< "ROUGNESS:" << std::endl;
    os<< "FULL PATH: "<< mat.roughness->type.getFullPath() << std::endl;
    os<<"SHADER NAME: "<<mat.roughness->shaderName<<std::endl;
    os<< "STATUS:" << std::endl;
    mat.roughness->type.wasFound ? std::cout<<"\xE2\x9C\x93"<<std::endl : std::cout<<"!!! TEXTURE WAS NOT FOUND !!!"<<std::endl;

    os<<"==================================================="<<std::endl;

    os<< "METALNESS:" << std::endl;
    os<<"STRENGTH: "<<mat.metalness->type.getFullPath()<<std::endl;
    os<<"SHADER NAME: "<<mat.metalness->shaderName<<std::endl;
    os<< "STATUS:" << std::endl;
    mat.metalness->type.wasFound ? std::cout<<"\xE2\x9C\x93"<<std::endl : std::cout<<"!!! TEXTURE WAS NOT FOUND !!!"<<std::endl;

    os<<"==================================================="<<std::endl;

    os<< "AO VALUES:" << std::endl;
    os<<"STRENGTH: "<<mat.ao->type.getFullPath()<<std::endl;
    os<<"SHADER NAME: "<<mat.ao->shaderName<<std::endl;
    os<< "STATUS:" << std::endl;
    mat.ao->type.wasFound ? std::cout<<" \xE2\x9C\x93 "<<std::endl : std::cout<<"!!! TEXTURE WAS NOT FOUND !!!"<<std::endl<<std::endl;

    return os;
}

PBRMaterial<Texture2D> *PBRTextured::getBaseColor() const {
    return baseColor;
}

PBRMaterial<Texture2D> *PBRTextured::getNormalMap() const {
    return normalMap;
}

PBRMaterial<Texture2D> *PBRTextured::getRoughness() const {
    return roughness;
}

PBRMaterial<Texture2D> *PBRTextured::getMetalness() const {
    return metalness;
}

PBRMaterial<Texture2D> *PBRTextured::getAo() const {
    return ao;
}

void PBRTextured::printLog() const {
    std::cout<<*this;
}
