//
// Created by wpsimon09 on 12/05/24.
//

#ifndef PABLO_RENDERER_MODELLOADERHELPER_H
#define PABLO_RENDERER_MODELLOADERHELPER_H

#include "Renderer/Utils/Vertex/Vertex.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"
#include "vector"

class ModelLoaderHelper {
public:
    static void processVertecies( std::vector<Vertex> &vertecies,aiMesh* mesh, const aiScene* scene );

    static void processIndecies(std::vector<unsigned int>&indecies, aiMesh*mesh);
};


#endif //PABLO_RENDERER_MODELLOADERHELPER_H
