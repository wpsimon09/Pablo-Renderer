//
// Created by wpsimon09 on 05/02/24.
//

#ifndef PABLO_RENDERER_OGLOBJECT_H
#define PABLO_RENDERER_OGLOBJECT_H

#include "glad/glad.h"

class OGLObject {
public:
    GLuint ID;
    virtual void bind(){};
    virtual void unbind(){};
};


#endif //PABLO_RENDERER_OGLOBJECT_H
