//
// Created by wpsimon09 on 03/01/24.
//

#ifndef PABLO_RENDERER_BASICMATERIALTEXTURED_H
#define PABLO_RENDERER_BASICMATERIALTEXTURED_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"

/***
 * Struct that holds information about the texture
 */
struct TextureUniform{
    std::string shaderName;
    TextureBase texture2D;

    /***
     * Creates instance of the texture unifrom
     * @param shaderName name of the unifrom in the shader
     * @param texture texture to be passed to the shader
     */
    TextureUniform(std::string shaderName, TextureBase texture){
        this->shaderName = shaderName;
        this->texture2D = std::move(texture);
    }
};

/***
 * Class representing material with single single texture
 */
class BasicMaterialTextured: public  Material{
public:

    /***
     * Creates instance of the class
     * @param shader shader that the material is using
     * @param path path to the texture that will be applied
     * @param shaderName name of the sampler uniform inside the shader
     */
    BasicMaterialTextured(std::shared_ptr<Shader> shader, const char* path, std::string shaderName = "FragmentColor");

    /***
     * Creates instance of the class
     * @param shader shader that the material is using
     * @param texture2D texture object that will be applied
     * @param shaderName name of the sampler unifrom inside the sader
     */
    BasicMaterialTextured(std::shared_ptr<Shader> shader, TextureBase texture2D, std::string shaderName = "FragmentColor");

    /**
     * Sends all fo the information to the shader
     */
    void configureShader() override;

    /***
     * Holds information about the generated or passed texture
     */
    std::unique_ptr<TextureUniform> texture;
};

#endif //PABLO_RENDERER_BASICMATERIALTEXTURED_H
