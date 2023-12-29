//
// Created by wpsimon09 on 29/12/23.
//

#ifndef CLIONTEST_POSTPROCESSING_H
#define CLIONTEST_POSTPROCESSING_H

#include "Texture/Texture.h"
#include "FrameBuffer/FrameBuffer.h"
#include "Shader.h"

class PostProcessing {
private:
    FrameBuffer* frameBuffer;
    Texture* drawnScene;
public:
    PostProcessing();
    PostProcessing(Texture * texture, FrameBuffer* FBO);
    void draw(Shader shader, unsigned  int VAO);
    unsigned int getTextureID();
    Texture* getTexture();
};


#endif //CLIONTEST_POSTPROCESSING_H
