//
// Created by wpsimon09 on 29/01/24.
//

#ifndef PABLO_RENDERER_MODELSCENENODE_H
#define PABLO_RENDERER_MODELSCENENODE_H

#include "Renderer/Renderable/Renderable.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/ai_assert.h>
#include <assimp/scene.h>
#include <vector>
#include "functional"
#include "thread"
#include "Renderer/SceneGraph/SceneNode/SceneNode.h"
#include "Renderer/Utils/ModelLoaderHelpers/ModelLoaderHelper.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2DArray.h"
#include "Renderer/Utils/ModelLoaderHelpers/MaterialsToProcess.h"
#include "Renderer/Utils/StopWatch/StopWatch.h"
#include "chrono"

class ModelSceneNode : public SceneNode {
public:
    explicit ModelSceneNode(std::string path, bool supportsAreaLight = false, std::shared_ptr<Material> mat = nullptr,
                            std::string name = "");

    std::string directory;
    std::string name;

    /***
     * Sets if the model is casting shadow
     * @param hasShadow bool is model an occluder @def false
     */
    void castsShadow(bool hasShadow = false);

    /***
     * Sets if the model is supporting image based lighting
     * @param supportsIBL true if model should support IBL
     * @note working IBL pipline has to be attached to the scene
     * @def ture
     */
    void supportsIbl(bool supportsIBL = true);

    bool checkStatus() { return this->wasFound; }

private:
    bool supportsIBL = false;

    bool supportsAreaLight = false;

    bool wasFound = false;

    bool hasEmissionTexture = false;

    int processedRenderableCount = 0;

    std::shared_ptr<Material> material = nullptr;

    std::shared_ptr<Shader> shader;

    std::vector<std::shared_ptr<Texture2D>> loadedTextures;

    std::vector<std::thread> threads;


    /***
     * Process node of the model from the assets
     * @param node node to process
     * @param scene scene in which the scene node is located
     */
    void processNode(aiNode *node, const aiScene *scene);

    /***
     * Process renderable of the mesh
     * @param mesh mesh to be processed
     * @param scene scene in which the model is located
     */
    void processRenderable(aiMesh *mesh, const aiScene *scene);


    std::unique_ptr<PBRTextured> processRenderableMaterial(aiMaterial *meshMaterial);

    std::unique_ptr<PBRMaterial<Texture2D>>
    processMaterialProperty(aiMaterial *material, aiTextureType type, const std::string &shaderName,
                            const int samplerID);

};


#endif //PABLO_RENDERER_MODELSCENENODE_H
