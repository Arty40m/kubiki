#pragma once
#include "../stl_headers.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


class Window
{
public:
    inline static int width = 640;
    inline static int height = 480;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    
    static Window& GetInstance();
    
    // Class methods
    inline static void Init(int width, int height) {Window::GetInstance()._Init(width, height);}
    inline static void PullEvents() {Window::GetInstance()._PullEvents();}
    inline static void SwapBuffers() {Window::GetInstance()._SwapBuffers();}
    inline static bool isShouldClose() {return Window::GetInstance()._isShouldClose();}
    inline static void close() {Window::GetInstance()._close();}
    inline static void clear() {Window::GetInstance()._clear();}
    inline static float getAspectRatio() {return Window::GetInstance()._getAspectRatio();}

    // Instance methods
    void _Init(int width, int height);
    void _PullEvents();
    inline void _SwapBuffers() const {glfwSwapBuffers(window);}
    inline bool _isShouldClose() const {return glfwWindowShouldClose(window);}
    inline void _close() const {glfwSetWindowShouldClose(window, true);}
    void _clear();
    inline float _getAspectRatio() const {return (float)Window::width / (float)Window::height;}

private:
    GLFWwindow* window;

    Window();
    ~Window();
};
