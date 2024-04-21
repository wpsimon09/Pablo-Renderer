cmake_minimum_required(VERSION 3.27)
project(Pablo-Renderer)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "source/*.cpp"
        "Includes/**/*.cpp"
        "Includes/Renderer/**/*.cpp"
)

file(GLOB_RECURSE HEADERS "Includes/**/*.h"
        "Includes/Renderer/**/*.h"
)

# Set where the ImGui files are stored
set(IMGUI_PATH  "3rdPartyLybraries/Includes/imgui")

# Compile as static library
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp
        ${IMGUI_PATH}/backends/imgui_impl_glfw.h
        ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp)

add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH}/backends)

# Add the source files
add_executable(${CMAKE_PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        Includes/Renderer/UI/UI.cpp
        Includes/Renderer/UI/UI.h
        Includes/Renderer/UI/Components/SceneMenu/SceneMenu.cpp
        Includes/Renderer/UI/Components/SceneMenu/SceneMenu.h
        Includes/Renderer/UI/Components/ViewPort/ViewPort.cpp
        Includes/Renderer/UI/Components/ViewPort/ViewPort.h
        Includes/Renderer/UI/Components/Component.cpp
        Includes/Renderer/UI/Components/Component.h
        Includes/Renderer/UI/Components/BottomMenu/BottomMenu.cpp
        Includes/Renderer/UI/Components/BottomMenu/BottomMenu.h
        Includes/Renderer/UI/Components/MaterialUI/MaterialUI.cpp
        Includes/Renderer/UI/Components/MaterialUI/MaterialUI.h
        Includes/Renderer/UI/Components/SceneNodeUI/SceneNodeUI.cpp
        Includes/Renderer/UI/Components/SceneNodeUI/SceneNodeUI.h
        Includes/Renderer/UI/Components/LightUI/LightUI.cpp
        Includes/Renderer/UI/Components/LightUI/LightUI.h
        Includes/Renderer/UI/Components/RenderableCreateationUI/RenderableCreationUI.cpp
        Includes/Renderer/UI/Components/RenderableCreateationUI/RenderableCreationUI.h
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Add the include directories
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/Includes
        ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes
        ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes/Renderer
        ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes/imgui
        ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes/imgui/backends

)


# Include and link Glad
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes/glad)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad)

add_library(glad STATIC 3rdPartyLybraries/Includes/glad/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/3rdPartyLybraries/Includes/glad)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ImGui)

# Find ASSIMP package and link against it
set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/assimp-5.0")
find_package(assimp REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE assimp)
set(BUILD_ASSIMP_TOOLS OFF)


# Find GLFW3 package and link against it
set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/glfw3")
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)


set(VERTEX_SHADER_DIR ${CMAKE_SOURCE_DIR}/VertexShader)
set(FRAGMENT_SHADER_DIR ${CMAKE_SOURCE_DIR}/FragmentShader)
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/Assets)
set(SOURCE ${CMAKE_SOURCE_DIR}/source)
set(INCLUDES ${CMAKE_SOURCE_DIR}/Includes)
set(3rdPARTY_LIBRARIES ${CMAKE_SOURCE_DIR}/3rdPartyLybraries)

set(OUT_VERTEX_SHADER_DIR ${CMAKE_BINARY_DIR})
set(OUT_FRAGMENT_SHADER_DIR ${CMAKE_BINARY_DIR})
set(OUT_ASSETS_DIR ${CMAKE_BINARY_DIR})
set(OUT_SOURCE ${CMAKE_BINARY_DIR})
set(OUT_INCLUDES ${CMAKE_BINARY_DIR})
set(OUT_3rdPARTY_LIBRARIES ${CMAKE_BINARY_DIR})

file(COPY ${VERTEX_SHADER_DIR} DESTINATION ${OUT_VERTEX_SHADER_DIR})
file(COPY ${FRAGMENT_SHADER_DIR} DESTINATION ${OUT_FRAGMENT_SHADER_DIR})
file(COPY ${ASSETS_DIR} DESTINATION ${OUT_ASSETS_DIR})
file(COPY ${SOURCE} DESTINATION ${OUT_SOURCE})
file(COPY ${INCLUDES} DESTINATION ${OUT_INCLUDES})
file(COPY ${3rdPARTY_LIBRARIES} DESTINATION ${OUT_3rdPARTY_LIBRARIES})

# Find ASSIMP package and link against it
set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/assimp-5.0")
find_package(assimp REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE assimp)
set(BUILD_ASSIMP_TOOLS ON)

#IAM GUI INTEGRATION