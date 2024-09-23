#pragma once
#include "stlh.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "KeyCodes.hpp"


class Window
{
public:
    inline static int width = 640;
    inline static int height = 480;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    
    static Window& GetI();
    
    // Instance methods
    void Init(int width, int height);
    void PullEvents();
    inline void SwapBuffers() const {glfwSwapBuffers(window);}
    inline bool isShouldClose() const {return glfwWindowShouldClose(window);}
    inline void close() const {glfwSetWindowShouldClose(window, true);}
    inline float getAspectRatio() const {return (float)Window::width / (float)Window::height;}

    inline double getTime() const {return glfwGetTime();}
    const std::string& getKeyName(int keycode) const;
    inline bool isKeyPressed(int keycode) const {return keyPressedArray[keycode];}

    inline float getCurKeyPressTime(int keycode) const {return curKeyPressTimeArray[keycode];}
    inline float getCurKeyReleaseTime(int keycode) const {return curKeyReleaseTimeArray[keycode];}
    inline float getPrevKeyPressTime(int keycode) const {return prevKeyPressTimeArray[keycode];}
    inline float getPrevKeyReleaseTime(int keycode) const {return prevKeyReleaseTimeArray[keycode];}

    inline std::pair<float, float> getPrevMousePos() const {return {prevMouseX, prevMouseY};}
    inline std::pair<float, float> getCurMousePos() const {return {curMouseX, curMouseY};}

private:
    GLFWwindow* window;
    std::vector<std::string> keyNameMap = createKeyNameMap();
    bool keyStateWasChanged[NUMBER_KEYS];
    bool keyPressedArray[NUMBER_KEYS];

    float curKeyPressTimeArray[NUMBER_KEYS];
    float curKeyReleaseTimeArray[NUMBER_KEYS];
    float prevKeyPressTimeArray[NUMBER_KEYS];
    float prevKeyReleaseTimeArray[NUMBER_KEYS];

    float prevMouseX;
    float prevMouseY;
    float curMouseX;
    float curMouseY;

    Window();
    ~Window();
};
