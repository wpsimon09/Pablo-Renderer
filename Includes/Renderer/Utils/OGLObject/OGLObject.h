//
// Created by wpsimon09 on 05/02/24.
//

#ifndef PABLO_RENDERER_OGLOBJECT_H
#define PABLO_RENDERER_OGLOBJECT_H

#include "glad/glad.h"

class OGLObject {
public:
    /***
     * Virtual method for binding
     */
    virtual void bind(){};

    /***
     * Virtual method for unbinding
     */
    virtual void unbind(){};
};


#endif //PABLO_RENDERER_OGLOBJECT_H
