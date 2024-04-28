//
// Created by wpsimon09 on 14/02/24.
//

#ifndef PABLO_RENDERER_BASICMATERIALCOLOR_H
#define PABLO_RENDERER_BASICMATERIALCOLOR_H

#include <utility>

#include "iostream"
#include "Renderer/Material/Material.h"

/***
 * Structure representing the uniform that stores basic color unifrom
 */
struct ColorUnifrom{
    std::string shaderName;
    glm::vec3 value;
    /***
     * Creates instance of the ColorUniform
     * @param shaderName name of the uniform in the shader
     * @param color color (rgb)
     */
    ColorUnifrom(std::string shaderName, glm::vec3 color){
        this->shaderName = std::move(shaderName);
        this->value = color;
    }
};

/***
 * Class representing material that has only single color
 */
class BasicMaterialColor:public Material {
public:
    /***
     * Creates instance of the BasicMaterialColor
     * @param shader shader that will be used by the material
     * @param color color of the material (rgb)
     * @param shaderName name of the uniform inside the shader
     */
    explicit BasicMaterialColor( glm::vec3 color = glm::vec3(1.0), std::string shaderName="lightColor");

    /***
     * Sends all of the relevant information to the shader
     */
    void configureShader() override;
private:
    std::unique_ptr<ColorUnifrom> color;
};


#endif //PABLO_RENDERER_BASICMATERIALCOLOR_H
