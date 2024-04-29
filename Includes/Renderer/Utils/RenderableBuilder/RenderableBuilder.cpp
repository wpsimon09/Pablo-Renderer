//
// Created by wpsimon09 on 24/04/24.
//

#include "RenderableBuilder.h"

std::unique_ptr<SceneNode> RenderableBuilder::buildRenderable() {
    try{

        std::shared_ptr<Geometry> geometry = nullptr;
        std::shared_ptr<Material> material = nullptr;

        std::string name = text;

        switch(selectedMateial){
            case TEXTURE:{
                 material = std::make_shared<PBRTextured>(textureDirectory, supportsIBL);
                break;
            }
            case COLOR:{
                material = std::make_shared<PBRColor>(color, supportsIBL);
                break;
            }
            default:{
                break;
            }

        }


        if(selectedGeometry != MODEL){
            /***
             * Switch for geometry creation
             */
            switch (selectedGeometry) {
                case CUBE:{
                    geometry = std::make_shared<CubeGeometry>();
                    break;
                }
                case SPHERE:{
                    geometry = std::make_shared<SphereGeometry>();
                    break;
                }
                case PLANE:{
                    geometry = std::make_shared<PlaneGeometry>();
                    break;
                }
                default:{
                    return nullptr;
                }
            }

            auto renderable = std::make_unique<Renderable>(geometry, material, name != ""? name: "renderable");
            renderable->castsShadwo = castsShadow;
            auto sceneNode = std::make_unique<SceneNode>(std::move(renderable));
            return sceneNode;

        }
        else{
            auto model = std::make_unique<ModelSceneNode>(modelOath, keepModelMaterial == false ? material : nullptr ,name);
            model->castsShadow(castsShadow);
            model->supportsIbl(supportsIBL);
            if(model->checkStatus()){
                return std::move(model);
            }else{
                return nullptr;
            }
        }
    }
    catch(std::exception e){
        return nullptr;
    }
}