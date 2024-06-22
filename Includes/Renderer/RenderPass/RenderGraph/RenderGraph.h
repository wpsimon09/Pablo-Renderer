//
// Created by wpsimon09 on 09/04/24.
//

#ifndef PABLO_RENDERER_RENDERGRAPH_H
#define PABLO_RENDERER_RENDERGRAPH_H

#include "Renderer/RenderPass/ScenePass/ScenePass.h"
#include "Renderer/RenderPass/ShadowMapPass/ShadowMapPass.h"
#include "Renderer/RenderPass/PostProcessingPasses/ChromaticAberration/ChromaticAberration.h"
#include "Renderer/RenderPass/PostProcessingPasses/Pixelation/Pixelation.h"
#include "Renderer/RenderPass/PostProcessingPasses/PostProcessingPass.h"
#include "Renderer/RenderPass/PixelPicking/PixelPicking.h"
#include "Renderer/Enums/RenderPassTypes.h"
#include "map"


class RenderGraph {
public:
    explicit RenderGraph(std::shared_ptr<Scene> scene);

    /***
     * Initialize render graph
     */
    void init();

    /***
     * Execture preprocessing like shadow generation
     */
    void preProcessing();

    /***
     * Execute acctual rendering of the scene
     */
    void render();

    /***
     * Executre post processing effects
     */
    void postProcessing();

    /***
     * Display results to the frame buffer
     * @param frameBuffer frame buffer into which the results should be copied
     */
    void displayResult(FrameBuffer &frameBuffer);

    /***
     * Reset texture counters etc...
     */
    void prepareForNextFrame();

    /***
     * Get the texture from the specified render pass
     * @param renderPass render pass from which to extract the texture (can be found in RenderPassTypes.h)
     * @return result of the render pass stored in the texture
     */
    std::shared_ptr<Texture2D> getDebugTexture(RENDER_PASS renderPass);

    FrameBuffer& getFrameBuffer(RENDER_PASS render_pass);
    /***
     * Returns vector of all render passes
     * @return vector of all render passes in renderer
     */
    std::vector<std::reference_wrapper<RenderPass>> getRenderPasses();
private:
    std::unique_ptr<RendererManager> rendererManager;
    std::map<RENDER_PASS, std::shared_ptr<Texture2D>> renderResults;

    //hardcoded for now later will be refactored (hopefully)
    std::unique_ptr<RenderPass> pixelPicking;
    std::unique_ptr<RenderPass> scenePass;
    std::unique_ptr<RenderPass> shadowMapPass;
    std::unique_ptr<RenderPass> chromaticAerrationPass;
    std::unique_ptr<RenderPass> pixelationPass;

    std::unique_ptr<PostProcessingPass> postProcessingPass;

    std::shared_ptr<Scene> scene;
};


#endif //PABLO_RENDERER_RENDERGRAPH_H
