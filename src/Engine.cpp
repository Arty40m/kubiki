#include "Engine.hpp"
#include "logging.hpp"
#include "Window/Window.hpp"



Engine::Engine():
    curFrameTime(0.0f),
    prevFrameTime(0.0f),
    isRunning(false){}

Engine::~Engine(){}

void Engine::shutdown()
{
    isRunning = false;
    Window::GetI().close();
}

void Engine::newFrame()
{
    prevFrameTime = curFrameTime;
    curFrameTime = glfwGetTime();
}

float Engine::getDeltaTime()
{
    return curFrameTime - prevFrameTime;
}

int Engine::run()
{
    isRunning = true;
    while (isRunning)
    {
        newFrame();
        onUpdate();
    }
    
    exit(EXIT_SUCCESS);
}