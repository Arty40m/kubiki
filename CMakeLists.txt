cmake_minimum_required(VERSION 3.8)

project(kubiki VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("deps/glfw")
add_subdirectory("deps/glad")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

set(IMGUI_SOURCES
    deps/imgui/imgui.cpp
    deps/imgui/imgui_draw.cpp
    deps/imgui/imgui_widgets.cpp
    deps/imgui/imgui_tables.cpp
    deps/imgui/imgui_demo.cpp
    deps/imgui/backends/imgui_impl_glfw.cpp
    deps/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(kubiki ${SRC_FILES} ${IMGUI_SOURCES})
                # src/main.cpp src/Application.cpp
                # src/Window/Window.cpp
                # src/Events/EventManager.cpp
                # src/DataStructures/DynamicBuffer.cpp
                # src/DataStructures/Stack.cpp

                # src/Graphic/Rendering/Renderer.cpp
                # src/Graphic/Rendering/Shader.cpp
                # src/Graphic/Rendering/glBuffers.cpp
                # src/Graphic/Rendering/Pipelines/PrimitivePipeline.cpp
                # src/Graphic/Rendering/Pipelines/SkyBoxPipeline.cpp

                # src/Camera/Camera.cpp


target_precompile_headers(kubiki PRIVATE src/stlh.hpp)

target_include_directories(kubiki PUBLIC "src/")
target_include_directories(kubiki PUBLIC "deps/glfw/include/")
target_include_directories(kubiki PUBLIC "deps/glad/include/")
target_include_directories(kubiki PUBLIC "deps/glm/")
target_include_directories(kubiki PUBLIC "deps/imgui/")
target_include_directories(kubiki PUBLIC "deps/imgui/backends/")

target_link_libraries(kubiki PRIVATE glfw)
target_link_libraries(kubiki PRIVATE glad)