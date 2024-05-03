# Pablo rendering engine

As title suggests Pablo is a rendering engine and OpenGL abstraction framework that supports PBR materials and 3D models together with 
**Image based lightning**

It provides fast and convenient way of rendering various geometry with different materials 

This renderer is build using 

**[GLFW](https://www.glfw.org)** for window management

**[GLM](https://glm.g-truc.net/0.9.9/index.html)** for mathematics 

**[GLAD](https://glad.dav1d.de)** for OpenGL functions initialization

**[Assimp](https://assimp-docs.readthedocs.io/en/v5.3.0/)** for model loading

**[Dear imgui](https://github.com/ocornut/imgui)** for UI


# Features 

- PBR shaders
- IBL (Image based lighting)
- Model loaders 
- Support for Normal mapping using normal maps in tangent space
- Anti aliasing up to 16x pixel samples
- Instance rendering 
- Transparent grid
- SkyBox
- Debug view for textures or frame buffer textures
- Flexible class structure
- SceneGraph design pattern
- Orbit camera
- Shadow mapping
- UI editor
- Model Loading from UI
- Area lights with LTCs (Linearly transform cosines)
----

# Example
To create sphere using IBL within the framework the code would look like this

```c++

//create an instance of PabloRenderer
auto pabloRenderer = PabloRenderer::getInstance();
pabloRenderer->init();

//create and ran IBL pipeline
auto iblPipeLine = std::make_shared<IBLPipeLine>("Assets/Textures/HDR/hill.hdr");
iblPipeLine->generateIBLTextures();

//load model 
auto pot = std::make_unique<ModelSceneNode>("Assets/Model/pot/brass_pot_01_2k.gltf");
pot->transformation->setScale(4.0f, 4.0f, 4.0f);
pot->castsShadow(true);

//create scene
std::shared_ptr<Scene> scene = std::make_shared<Scene>();

//attach IBL pipeline to have image based lightning
scene->setIblPipeLine(iblPipeLine);

//attach scene to the PabloRenderer
pabloRenderer->attachScene(scene);

//render the attached scene
pabloRenderer->render();
```

The result of the snippet will look like this (after small alterations using UI)

Or we can simply do it via UI by clicking `Add new` button and following instructions on the screen

![img.png](Assets/ReadmeImages/pablo-tutorial.png)

As of now renderer's shader only support one directional light and 1 area light if selected which is going to change in the near future

# Images
![Pablo](Assets/ReadmeImages/pablo-4.png)



![Area light](Assets/ReadmeImages/area-light.png)




