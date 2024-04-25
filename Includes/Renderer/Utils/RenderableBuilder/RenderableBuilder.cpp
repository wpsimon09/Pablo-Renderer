//
// Created by wpsimon09 on 24/04/24.
//

#include "RenderableBuilder.h"

std::unique_ptr<Renderable> RenderableBuilder::buildRenderable() {
    try{

        std::shared_ptr<Geometry> geometry = nullptr;
        std::shared_ptr<PBRColor> materialColor = nullptr;
        std::shared_ptr<PBRTextured> materialTextured = nullptr;

        std::string name = text;

        switch(selectedMateial){
            case TEXTURE:{
                materialTextured = std::make_shared<PBRTextured>(textureDirectory);
                break;
            }
            case COLOR:{
                materialColor = std::make_shared<PBRColor>(color);
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
        }
        else{
            auto model = std::make_unique<ModelSceneNode>(modelOath, keepModelMaterial == false ? materialTextured : nullptr );
            model->castsShadow(castsShadow);
            if(model->checkStatus()){
                return model;
            }else{
                return nullptr;
            }
        }
    }
}
