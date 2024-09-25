#include "Application.hpp"
#include "Window/Window.hpp"
#include "Events/Event.hpp"
#include "Events/Events.hpp"
#include "Events/EventManager.hpp"
#include "Window/KeyCodes.hpp"
#include "DataStructures/Stack.hpp"

#include "Graphic/Graphic.hpp"
#include "Camera/Camera.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/ext.hpp>


static bool trCallback(Triangle* t, Event* e)
{
    if (!Window::GetI().isKeyPressed(LEFT_MOUSE_BUTTON)){
        return true;
    }

    MouseMovedEvent* E = (MouseMovedEvent*)e;
    float dx = E->dx;
    float dy = E->dy;

    t->translate({dx*0.01f, -dy*0.01f, 0.0f});
    return true;
}

static bool scrollCallback(Triangle* t, Event* e)
{
    MouseScrolledEvent* E = (MouseScrolledEvent*)e;
    t->translate({0.0f, 0.0f, 0.1f * E->offset});
    return true;
}

static bool walkCallback(Camera* camera, Event* e)
{
    KeyPressedEvent* E = (KeyPressedEvent*)e;
    int keycode = E->keycode;
    float sens = 0.005;

    if (keycode==KEY_D || keycode==KEY_A)
    {
        float sign = (keycode==KEY_D) ? 1.0f : -1.0f;
        glm::vec3 right = glm::normalize(glm::cross(camera->dir, camera->upv));
        camera->pos += sens * sign * right;
    }
    else if (keycode==KEY_W || keycode==KEY_S)
    {
        float sign = (keycode==KEY_W) ? 1.0f : -1.0f;
        camera->pos += sens * sign * camera->dir;
    }
    else if (keycode==KEY_SPACE || keycode==KEY_LEFT_SHIFT)
    {
        float sign = (keycode==KEY_SPACE) ? 1.0f : -1.0f;
        camera->pos.y += sens * sign;
    }

    return true;
}

static bool cameraMoveCallback(Camera* camera, Event* e)
{
    MouseMovedEvent* E = (MouseMovedEvent*)e;
    float dy = E->dy;
    float dx = E->dx;

    float clipPitch = glm::pi<float>() * 2.0f / 180.0f;
    float yaw = camera->yaw + 0.001 * E->dx;
    float pitch = camera->pitch - 0.001 * E->dy;

    if (yaw < 0){
        yaw = 2.0f * glm::pi<float>() + yaw;
    } else if (yaw > 2.0f * glm::pi<float>()){
        yaw = yaw - 2.0f * glm::pi<float>();
    }
    
    if (pitch < clipPitch){
        pitch = clipPitch;
    } else if (pitch > (glm::pi<float>() - clipPitch)){
        pitch = glm::pi<float>() - clipPitch;
    }

    float sin_pitch = std::sin(pitch);
    float cos_pitch = std::cos(pitch);
    float sin_yaw = std::sin(yaw);
    float cos_yaw = std::cos(yaw);

    glm::vec3 dir = glm::vec3(-sin_pitch*sin_yaw, -cos_pitch, sin_pitch*cos_yaw);
    camera->dir = glm::normalize(dir);
    camera->yaw = yaw;
    camera->pitch = pitch;
    
    return true;
}

int Application::run()
{
    Window::GetI().Init(1024, 768);
    Renderer::GetI().Init();
    EventManager::GetI().Init();

    Camera camera;

    PrimitivePipeline primitivePipe;
    primitivePipe.camera = &camera;
    primitivePipe.shader.Init("D:\\kubiki\\resources\\shaders\\vertex.shader", "D:\\kubiki\\resources\\shaders\\fragment.shader");
    
    Triangle triangle2({2.0f, 0.0f, 1.0f});
    primitivePipe.addMesh(&triangle2.mesh);
    Triangle triangle;
    primitivePipe.addMesh(&triangle.mesh);

    std::vector<Cube> cubeVec;
    for (int x=-50; x<50; x+=2){
        for (int z=-50; z<50; z+=2){
            glm::vec3 pos = {(float)x, -2.0f, (float)z};
            cubeVec.emplace_back(pos);
        }
    }

    for (int i=0; i<cubeVec.size(); i++){
        primitivePipe.addMesh(&(cubeVec[i].mesh));
    }

    primitivePipe.enable();
    Renderer::GetI().addPipeline("PrimitivePipeline", &primitivePipe);


    SkyBoxPipeline skyboxPipe;
    skyboxPipe.camera = &camera;
    skyboxPipe.shader.Init("D:\\kubiki\\resources\\shaders\\skyBoxVertex.shader", "D:\\kubiki\\resources\\shaders\\skyBoxFragment.shader");
    skyboxPipe.enable();
    Renderer::GetI().addPipeline("SkyBoxPipeline", &skyboxPipe);

    // EventManager::GetI().addCallback(Event::EventType::MOUSE_MOVED_E, std::bind(trCallback, &triangle, std::placeholders::_1));
    // EventManager::GetI().addCallback(Event::EventType::MOUSE_SCROLLED_E, std::bind(scrollCallback, &triangle, std::placeholders::_1));

    EventManager::GetI().addCallback(Event::EventType::KEY_PRESSED_E, std::bind(walkCallback, &camera, std::placeholders::_1));
    EventManager::GetI().addCallback(Event::EventType::MOUSE_MOVED_E, std::bind(cameraMoveCallback, &camera, std::placeholders::_1));

    EventManager::GetI().addCallback(Event::EventType::KEY_PRESSED_E, [](Event* e){
        KeyPressedEvent* E = (KeyPressedEvent*)e;
        if (E->keycode == KEY_ESCAPE){
            Window::GetI().close();
        }
        return true;
    });

    while (!Window::GetI().isShouldClose())
    {
        Window::GetI().SwapBuffers();
        Renderer::GetI().clear();
        Window::GetI().PullEvents();
        EventManager::GetI().processEvents();

        Renderer::GetI().render();
    }

    exit(EXIT_SUCCESS);
}