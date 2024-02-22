//
// Created by wpsimon09 on 30/12/23.
//

#ifndef PABLO_RENDERER_DEBUGLOGGER_H
#define PABLO_RENDERER_DEBUGLOGGER_H
#include "glad.h"
#include "iostream"
GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)
#endif //PABLO_RENDERER_DEBUGLOGGER_H
