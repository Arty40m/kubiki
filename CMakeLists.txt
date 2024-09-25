cmake_minimum_required(VERSION 3.8)

project(kubiki VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("deps/glfw")
add_subdirectory("deps/glad")

add_executable(kubiki
                src/main.cpp src/Application.cpp
                src/Window/Window.cpp
                src/Events/EventManager.cpp
                src/DataStructures/DynamicBuffer.cpp
                src/DataStructures/Stack.cpp

                src/Graphic/Rendering/Renderer.cpp
                src/Graphic/Rendering/Shader.cpp
                src/Graphic/Rendering/glBuffers.cpp
                src/Graphic/Rendering/Pipelines/PrimitivePipeline.cpp
                src/Graphic/Rendering/Pipelines/SkyBoxPipeline.cpp

                src/Camera/Camera.cpp
)

target_precompile_headers(kubiki PRIVATE src/stlh.hpp)

target_include_directories(kubiki PUBLIC "src/")
target_include_directories(kubiki PUBLIC "deps/glfw/include/")
target_include_directories(kubiki PUBLIC "deps/glad/include/")
target_include_directories(kubiki PUBLIC "deps/glm/")

target_link_libraries(kubiki PRIVATE glfw)
target_link_libraries(kubiki PRIVATE glad)