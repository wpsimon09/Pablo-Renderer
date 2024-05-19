//
// Created by wpsimon09 on 19/05/24.
//

#include "Texture2DArray.h"

void Texture2DArray::bind() {

    TextureBase::bind();
}

void Texture2DArray::unbind() {
    TextureBase::unbind();
}

Texture2DArray::Texture2DArray(std::vector<std::shared_ptr<Texture2D>> texs) {
    try {
        this->isValidArray(texs);

        this->textures = texs;

        glCreateTextures(GL_TEXTURE_2D_ARRAY,1, &this->ID);
        glCheckError();

        glTextureStorage3D(this->ID, 1, textures[0]->getInternalFormat(), textures[0]->texWidth, textures[0]->texHeight, textures.size());
        glCheckError();

        for (int i = 0; i < this->textures.size(); ++i) {
            glTextureSubImage3D(this->ID, 0, 0,0, i,textures[0]->texWidth, textures[0]->texWidth, 1, GL_RGBA, GL_UNSIGNED_BYTE, );
        }

    }catch (std::invalid_argument &e){
        std::cerr<<e.what();
    }
}

bool Texture2DArray::isValidArray(std::vector<std::shared_ptr<Texture2D>> texutres) {
    if(!texutres.empty()) {
        auto width = textures[0]->texWidth;
        auto height = texutres[0]->texHeight;
        for (auto &texture: texutres) {
            if(texture->texWidth != width || texture->texHeight != height){
                throw std::invalid_argument("Dimensions of the textures in the vector does not match");
            }
        }
        return true;
    }
    throw std::invalid_argument("The vector is empty");
}





