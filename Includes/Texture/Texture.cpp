//
// Created by wpsimon09 on 23/12/23.
//
#include "Texture.h"

#include "Debug/DebugLogger.h"

Texture::Texture(GLenum type,const char*shaderName, glm::vec2 dimensions, GLenum colorChannels,GLenum internalFomrat) {
    glGenTextures(1, &this->ID);
    glBindTexture(type, this->ID);
    this->dimensions = dimensions;
    this->shaderName = shaderName;
    if (type == GL_TEXTURE_CUBE_MAP)
    {
        for (int i = 0; i < 6; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, internalFomrat, this->dimensions.x, this->dimensions.y, 0, colorChannels, GL_FLOAT, nullptr);
        }
        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else if (type == GL_TEXTURE_2D)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFomrat, this->dimensions.x, this->dimensions.y, 0, colorChannels, GL_FLOAT,nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    this->type=type;

    std::cout<<"Texture generated with the following options"<<std::endl;
    std::cout<<"Type: "<<this->type<<std::endl;
    std::cout<<"Shader name: "<<this->shaderName<<std::endl;
    std::cout<<"ID: "<<this->ID<<std::endl;

}

glm::vec2 Texture::getDimentions() {
    return this->dimensions;
}

void Texture::updateDimentions(glm::vec2 dimentions) {
    this->dimensions=dimentions;
}

void Texture::changeFilteringMethod(GLenum mag, GLenum min) {
    glBindTexture(this->type, this->ID);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, mag);
}

void Texture::generateMipmap() {
    glBindTexture(this->type, this->ID);
    glCheckError();
    glGenerateMipmap(this->type);
    glCheckError();
    glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glCheckError();
    glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glCheckError();
    std::cout<<" Generated mip map for the texture with ID: "<<this->ID<<std::endl;
}

void Texture::changeWrappingMethod(GLenum s, GLenum t, GLenum r) {
    glBindTexture(this->type, this->ID);
    glTexParameteri(this->type, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(this->type, GL_TEXTURE_WRAP_T, t);
    if (this->type == GL_TEXTURE_CUBE_MAP){
        glTexParameteri(this->type, GL_TEXTURE_WRAP_T, r);
    }

}
