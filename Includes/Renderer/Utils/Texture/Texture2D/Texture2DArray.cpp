//
// Created by wpsimon09 on 19/05/24.
//

#include "Texture2DArray.h"


Texture2DArray::Texture2DArray(std::vector<std::unique_ptr<Texture2D>> texs) {
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

        glTextureStorage3D(this->ID, 1, textures[0]->getInternalFormat(), textures[0]->texWidth, textures[0]->texHeight, textures.size());
        glCheckError();

        for (int i = 0; i < this->textures.size(); ++i) {
            glTextureSubImage3D(this->ID, 0, 0,0, i,textures[0]->texWidth, textures[0]->texWidth, 1, GL_RGBA, GL_UNSIGNED_BYTE, textures[i]->getData());
            this->textureCount ++;
        }

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





