//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_TEXTURE2D_H
#define PABLO_RENDERER_TEXTURE2D_H

#include "glad.h"
#include "stb_image.h"
#include "iostream"

class Texture2D {
public:
    GLuint ID;
    explicit Texture2D(const char* path);
private:

};


#endif //PABLO_RENDERER_TEXTURE2D_H
