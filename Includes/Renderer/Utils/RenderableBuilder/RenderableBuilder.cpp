//
// Created by wpsimon09 on 24/04/24.
//

#include "RenderableBuilder.h"

std::unique_ptr<Renderable> RenderableBuilder::buildRenderable() {
    std::unique_ptr<Geometry> geometry = nullptr;
    std::unique_ptr<ModelSceneNode> model = nullptr;
    std::shared_ptr<Material> material = nullptr;

    switch(selectedMateial){
        case TEXTURE:{
            material = std::make_shared<PBRTextured>(textureDirectory);
            break;
        }
        case COLOR:{
            material = std::make_shared<PBRColor>(color);
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
                geometry = std::make_unique<CubeGeometry>();
                break;
            }
            case SPHERE:{
                geometry = std::make_unique<SphereGeometry>();
                break;
            }
            case PLANE:{
                geometry = std::make_unique<PlaneGeometry>();
                break;
            }
            default:{
                return nullptr;
            }
        }
    }
    else{
        model = std::make_unique<ModelSceneNode>(modelOath);
        if(model->checkStatus()){
            if(!keepModelMaterial && material != nullptr){
                model->setMaterial(material);
            }
            return std::make_unique<Renderable>(geometry, material,text);
        }else{
            return nullptr;
        }
    }
}
