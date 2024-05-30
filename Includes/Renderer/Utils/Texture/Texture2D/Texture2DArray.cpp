//
// Created by wpsimon09 on 19/05/24.
//

#include "Texture2DArray.h"

Texture2DArray::Texture2DArray():TextureBase() {
    this->isPBRMaterial = false;
    this->type = GL_TEXTURE_2D_ARRAY;
    this->type_string = "GL_TEXTURE_2D_ARRAY";
}

Texture2DArray::Texture2DArray(std::vector<std::unique_ptr<Texture2D>> texs):TextureBase() {
    this->isPBRMaterial = false;
    this->type = GL_TEXTURE_2D_ARRAY;
    this->type_string = "GL_TEXTURE_2D_ARRAY";
    this->textures = std::move(texs);
    this->loadToGL();
}

void Texture2DArray::bind() {
    TextureBase::bind();
}

void Texture2DArray::unbind() {
    TextureBase::unbind();
}

void Texture2DArray::add(std::unique_ptr<Texture2D> texture) {
    this->textures.push_back(std::move(texture));
}

void Texture2DArray::loadToGL() {
    try {
        this->areTexturesValid();

        glCreateTextures(GL_TEXTURE_2D_ARRAY,1, &this->ID);
        glCheckError();

        glBindTexture(GL_TEXTURE_2D_ARRAY, this->ID);
        glCheckError();

        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA, textures[0]->texWidth, textures[0]->texHeight, textures.size());
        glCheckError(); //GL_INVALID_OPERATION

        for (int i = 0; i < this->textures.size(); ++i) {

            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i,textures[0]->texWidth, textures[0]->texWidth, 1, GL_RGBA, GL_UNSIGNED_BYTE, textures[i]->getData());
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
            if(texture->texWidth != width || texture->texHeight != height){
                throw std::domain_error("Dimensions of the textures in the vector does not match");
            }
        }
        return true;
    }
    throw std::domain_error("The vector is empty");

}






