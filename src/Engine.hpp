#pragma once
#include "stlh.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>



class Engine
{
public:
    Engine();
    ~Engine();

    void shutdown();
    inline double getTime() const {return glfwGetTime();}
    void newFrame();
    float getDeltaTime();
    int run();
    virtual void onUpdate() = 0;

private:
    float curFrameTime, prevFrameTime;
    bool isRunning;
};


