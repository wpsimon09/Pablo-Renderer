//
// Created by wpsimon09 on 17/05/24.
//

#ifndef PABLO_RENDERER_UNCOMPILEDSHADERS_H
#define PABLO_RENDERER_UNCOMPILEDSHADERS_H

#include "iostream"
#include "Renderer/Enums/ShaderTypes.h"
#include "vector"

struct UncompiledShader{
    std::string vertexPath;
    std::string fragmentPath;
    std::string name;
    ShaderType type;
    UncompiledShader(ShaderType type,std::string vertexP, std::string fragmentP, std::string name){
        this->vertexPath= std::move(vertexP);
        this->fragmentPath = std::move(fragmentP);
        this->name = std::move(name);
        this->type = type;
    }
};

std::vector<UncompiledShader> __uncompiledShaders = {
        UncompiledShader(SHADER_HDR_2_CUBE_MAP, "VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "HDR TO CUBE MAP"),
        UncompiledShader(SHADER_GENERATE_IRRADIANCE, "VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/EnviromentToIrradianceFragment.glsl", "CUBE MAP TO IRRADIANCE"),
        UncompiledShader(SHADER_GENERATE_PREFILTER, )

};

#endif //PABLO_RENDERER_UNCOMPILEDSHADERS_H
