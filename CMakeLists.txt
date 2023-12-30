cmake_minimum_required(VERSION 3.27)
project(Pablo-Renderer)

set(CMAKE_CXX_STANDARD 23)


# Add the source files
add_executable(${CMAKE_PROJECT_NAME} source/main.cpp
        source/stb_image.cpp
        Includes/FrameBuffer/FrameBuffer.h
        Includes/FrameBuffer/FrameBuffer.cpp
        Includes/Texture/Texture.h
        Includes/FrameBuffer/FrameBuffer.cpp
        Includes/Texture/Texture.cpp
        Includes/PBRPipeline/PBRPipeline.cpp
        Includes/PBRPipeline/PBRPipeline.h
        Includes/PBRPipeline/PBRPipeline.h
        Includes/Debug/DisplayingFrameBuffer/FrameBufferDebug.cpp
        Includes/Debug/DisplayingFrameBuffer/FrameBufferDebug.h
        Includes/PostProcessing/PostProcessing.cpp
        Includes/PostProcessing/PostProcessing.h
        Includes/Renderer/Utils/Vertex/Vertex.cpp
        Includes/Renderer/Utils/Vertex/Vertex.h
        Includes/Renderer/Renderable/Renderable.cpp
        Includes/Renderer/Renderable/Renderable.h
        Includes/Renderer/Utils/Transformations/Transformations.cpp
        Includes/Renderer/Utils/Transformations/Transformations.h
        Includes/Renderer/Geometry/Geometry.cpp
        Includes/Renderer/Geometry/Geometry.h
        Includes/Renderer/Material/Material.cpp
        Includes/Renderer/Material/Material.h
        Includes/Renderer/Geometry/Shapes/CubeGeometry.cpp
        Includes/Renderer/Geometry/Shapes/CubeGeometry.h
        Includes/Renderer/Geometry/Shapes/cubeVerticies.h
        Includes/Renderer/Utils/VAO/VAO.cpp
        Includes/Renderer/Utils/VAO/VAO.h
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Add the include directories
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/Includes
        ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes
        ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes/Renderer)


# Include and link Glad
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes/glad)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad)

add_library(glad STATIC 3rdPartyLybraries/Includes/glad/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes/glad)

# Find ASSIMP package and link against it
set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/assimp-5.0")
find_package(assimp REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE assimp)

# Find GLFW3 package and link against it
set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/glfw3")
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)

