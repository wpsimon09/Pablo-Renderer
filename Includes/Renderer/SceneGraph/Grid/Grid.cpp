//
// Created by wpsimon09 on 04/02/24.
//

#include "Grid.h"

Grid::Grid(Shader *shader): SceneNode(){
    PBRTextured* mat = new PBRTextured(shader,"Assets/Textures/PBR/ForestRock");
    Geometry* geometry = new PlaneGeometry();
    Renderable* gridRenderable = new Renderable(geometry, mat);
    this->addChild(new SceneNode(gridRenderable));
    //mat->printLog();
}

Material *Grid::generateFloorTexture() {

    /*
    FrameBuffer proceduralTextureFrameBuffer;
    Texture *girdProceduralTexture = new Texture(GL_TEXTURE_2D, "gridTexture", glm::vec2(512, 512), GL_RGBA, GL_RGBA);
    proceduralTextureFrameBuffer.mountTexture(girdProceduralTexture);
    girdProceduralTexture->changeWrappingMethod(GL_REPEAT, GL_REPEAT);
    proceduralTextureFrameBuffer.updateRenderBufferStorage(girdProceduralTexture->getDimentions());
    proceduralFloorTextureShader.use();
    proceduralFloorTextureShader.setFloat("numOfDivisions", 1.2);
    proceduralTextureFrameBuffer.drawToTexture(proceduralFloorTextureShader, planeVAO);
    */

}

