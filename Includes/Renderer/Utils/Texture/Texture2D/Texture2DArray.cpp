//
// Created by wpsimon09 on 19/05/24.
//

#include "Texture2DArray.h"

Texture2DArray::Texture2DArray():TextureBase() {
    this->isPBRMaterial = false;
    this->type = GL_TEXTURE_2D_ARRAY;
    this->type_string = "GL_TEXTURE_2D_ARRAY";

    glCreateTextures(GL_TEXTURE_2D_ARRAY,1, &this->ID);
    glCheckError();
}

Texture2DArray::Texture2DArray(std::vector<std::shared_ptr<Texture2D>> texs):TextureBase() {


    this->isPBRMaterial = false;
    this->type = GL_TEXTURE_2D_ARRAY;
    this->type_string = "GL_TEXTURE_2D_ARRAY";
    this->textures = texs;

    glCreateTextures(GL_TEXTURE_2D_ARRAY,1, &this->ID);
    glCheckError();

    this->loadToGL();
}

void Texture2DArray::bind() {
    TextureBase::bind();
}

void Texture2DArray::unbind() {
    TextureBase::unbind();
}

void Texture2DArray::add(std::shared_ptr<Texture2D> texture) {
    this->textures.push_back(std::move(texture));
}

void Texture2DArray::loadToGL() {
    try {
        this->areTexturesValid();

        glBindTexture(GL_TEXTURE_2D_ARRAY, this->ID);
        glCheckError();

        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, textures[0]->texWidth, textures[0]->texHeight, this->textures.size());
        glCheckError(); //segmentation fault here

        for (int i = 0; i < this->textures.size(); i++) {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i,textures[0]->texWidth, textures[0]->texHeight, 1, GL_RGB, GL_UNSIGNED_BYTE, this->textures[i]->getData());
            glCheckError(); //GL_INVALID_OPERATION
            textures[i]->clearTextureData();
            this->textureCount ++;
        }

        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    }catch (std::domain_error &e){
        std::cerr<<e.what();
    }
}


bool Texture2DArray::areTexturesValid() {
    if(!this->textures.empty()) {
        auto width = textures[0]->texWidth;
        auto height = textures[0]->texHeight;
        for (auto &texture: textures) {
            if(texture->texWidth != width || texture->texHeight != height || texture->getData() == nullptr){
                throw std::domain_error("Dimensions of the textures in the vector does not match");
            }
        }
        return true;
    }
    throw std::domain_error("The vector is empty");

}






