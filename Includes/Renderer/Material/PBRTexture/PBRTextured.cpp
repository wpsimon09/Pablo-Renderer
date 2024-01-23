//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(Shader* shader, std::string pathToTheDirectory, std::string shaderNamingConvention, std::string fileFormat): Material(shader) {
    Texture2D albedo((pathToTheDirectory+"/albedo"+fileFormat).c_str(), true);
    this->baseColor = new PBRMaterial<Texture2D>(albedo, shaderNamingConvention+"albedoMap");
    this->baseColor->type.setSamplerID(0);

    Texture2D rougness((pathToTheDirectory+"/roughness"+ fileFormat).c_str(), true);
    this->roughness = new PBRMaterial<Texture2D>(rougness, shaderNamingConvention+"rougnessMap");
    this->roughness->type.setSamplerID(1);

    Texture2D metallic((pathToTheDirectory+"/metallic"+ fileFormat).c_str(), true);
    this->metalness = new PBRMaterial<Texture2D>(metallic, shaderNamingConvention+"metallnesMap");
    this->metalness->type.setSamplerID(2);

    Texture2D normal((pathToTheDirectory+"/normal"+ fileFormat).c_str(), true);
    this->normalMap = new PBRMaterial<Texture2D>(normal, shaderNamingConvention+"normalMap");
    this->normalMap->type.setSamplerID(3);

    Texture2D _ao((pathToTheDirectory + "/ao" + fileFormat).c_str(), true);
    this->ao = new PBRMaterial<Texture2D>(_ao, shaderNamingConvention + "aoMap");
    this->ao->type.setSamplerID(4);
}

std::ostream &operator<<(std::ostream &os, const PBRTextured &mat) {
    os<<"PBR material using TEXTURES has following properties"<<std::endl;

    os<<"===================================================="<<std::endl;
    os<<"SHADER: "<<mat.shader->name<<std::endl;
    os<<"===================================================="<<std::endl;

    os<<"==================================================="<<std::endl;

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
    os<<"FULL PATH: "<<mat.metalness->type.getFullPath()<<std::endl;
    os<<"SHADER NAME: "<<mat.metalness->shaderName<<std::endl;
    os<< "STATUS:" << std::endl;
    mat.metalness->type.wasFound ? std::cout<<"\xE2\x9C\x93"<<std::endl : std::cout<<"!!! TEXTURE WAS NOT FOUND !!!"<<std::endl;

    os<<"==================================================="<<std::endl;

    os<< "AO VALUES:" << std::endl;
    os<<"FULL PATH: "<<mat.ao->type.getFullPath()<<std::endl;
    os<<"SHADER NAME: "<<mat.ao->shaderName<<std::endl;
    os<< "STATUS: " << std::endl;
    mat.ao->type.wasFound ? std::cout<<" \xE2\x9C\x93 "<<std::endl : std::cout<<"!!! TEXTURE WAS NOT FOUND !!!"<<std::endl<<std::endl;

    os<<"==================================================="<<std::endl;

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

void PBRTextured::configureShader() {
    this->shader->use();

    this->shader->setInt(this->baseColor->shaderName, this->baseColor->type.getSamplerID());
    glActiveTexture(GL_TEXTURE0 + this->baseColor->type.getSamplerID());
    glBindTexture(GL_TEXTURE_2D, this->baseColor->type.ID);

    this->shader->setInt(this->ao->shaderName, this->ao->type.getSamplerID());
    glActiveTexture(GL_TEXTURE0 + this->ao->type.getSamplerID());
    glBindTexture(GL_TEXTURE_2D, this->ao->type.ID);

    this->shader->setInt(this->metalness->shaderName, this->metalness->type.getSamplerID());
    glActiveTexture(GL_TEXTURE0 + this->metalness->type.getSamplerID());
    glBindTexture(GL_TEXTURE_2D, this->metalness->type.ID);

    this->shader->setInt(this->roughness->shaderName, this->roughness->type.getSamplerID());
    glActiveTexture(GL_TEXTURE0 + this->roughness->type.getSamplerID());
    glBindTexture(GL_TEXTURE_2D, this->roughness->type.ID);

    this->shader->setInt(this->normalMap->shaderName, this->normalMap->type.getSamplerID());
    glActiveTexture(GL_TEXTURE0 + this->normalMap->type.getSamplerID());
    glBindTexture(GL_TEXTURE_2D, this->normalMap->type.ID);

    //configure samplers
    //configure pbr shader to accept naming convention
    //set rendering to set the current samplers
}
