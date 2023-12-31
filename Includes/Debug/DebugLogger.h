//
// Created by wpsimon09 on 30/12/23.
//

#ifndef PABLO_RENDERER_DEBUGLOGGER_H
#define PABLO_RENDERER_DEBUGLOGGER_H
#include "glad.h"
#include "iostream"
GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" <<
                  std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#endif //PABLO_RENDERER_DEBUGLOGGER_H
