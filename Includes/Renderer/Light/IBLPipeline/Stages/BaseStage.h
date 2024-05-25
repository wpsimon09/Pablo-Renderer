//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_BASESTAGE_H
#define PABLO_RENDERER_BASESTAGE_H

#include "Renderer/Utils/FrameBuffer/FrameBufferCube/FrameBufferCube.h"
#include "Renderer/Utils/Texture/TextureBase.h"
#include "Renderer/Utils/ShaderManager/ShaderManager.h"

/***
 * Stage of the IBL pipeline that is meant to be inherited by concrete steps
 */
class BaseStage {
protected:
    bool fistExecution = true;

    BaseStage() =default ;

    /***
     * Shader for the concrete stege
     */
    std::shared_ptr<Shader> shader;
public:
    /***
     * Executes the concrete stage
     * @param input input texture should be HDR texture or HDR converted to cube map
     */
    virtual void execute(TextureBase input){};

    /***
     * Binds all textures to texture targets to 0
     */
    virtual void clearBindings(){}

    /***
     * Result of the stage
     */
    std::shared_ptr<TextureBase> result;

    /***
     * Name of the shader uniform where the texture will be uploaded
     */
    std::string shaderName;

    bool isExecutingFirstTime() {return fistExecution;}
};


#endif //PABLO_RENDERER_BASESTAGE_H
