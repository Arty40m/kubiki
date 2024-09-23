#include "Application.hpp"
#include "Window/Window.hpp"
#include "Events/Event.hpp"
#include "Events/Events.hpp"
#include "Events/EventManager.hpp"
#include "Window/KeyCodes.hpp"
#include "DataStructures/Stack.hpp"

#include "Graphic/Graphic.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/ext.hpp>


bool trCallback(Triangle* t, Event* e)
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

bool scrollCallback(Triangle* t, Event* e)
{
    MouseScrolledEvent* E = (MouseScrolledEvent*)e;
    t->translate({0.0f, 0.0f, 0.1f * E->offset});
    return true;
}

int Application::run()
{
    Window::GetI().Init(640, 480);
    Renderer::GetI().Init();
    EventManager::GetI().Init();

    PrimitivePipeline testPipe;
    testPipe.shader.Init("D:\\kubiki\\resources\\shaders\\vertex.shader", "D:\\kubiki\\resources\\shaders\\fragment.shader");
    
    Triangle triangle;
    testPipe.addMesh(&triangle.mesh);
    testPipe.enable();
    Renderer::GetI().addPipeline("PrimitivePipeline", &testPipe);

    EventManager::GetI().addCallback(Event::EventType::MOUSE_MOVED_E, std::bind(trCallback, &triangle, std::placeholders::_1));
    EventManager::GetI().addCallback(Event::EventType::MOUSE_SCROLLED_E, std::bind(scrollCallback, &triangle, std::placeholders::_1));

    EventManager::GetI().addCallback(Event::EventType::MOUSE_RELEASED_E, [](Event* e){
        LOG_INFO("{}", e->repr());
        EventManager::GetI().emplaceEvent<TestEvent>();
        return true;
    });

    EventManager::GetI().addCallback(Event::EventType::TEST_E, [](Event* e){
        LOG_INFO("TEST E created: {}", e->repr());
        return true;});

    EventManager::GetI().addCallback(Event::EventType::KEY_PRESSED_E, [](Event* e){
        KeyPressedEvent* E = (KeyPressedEvent*)e;
        if (E->keycode == KEY_ESCAPE){
            Window::GetI().close();
        }
        return true;
    });

    EventManager::GetI().addCallback(Event::EventType::KEY_RELEASED_E, [](Event* e){
        LOG_INFO("{}", e->repr());
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