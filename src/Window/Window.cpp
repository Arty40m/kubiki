#include "Window.hpp"
#include "logging.hpp"

#include "../Events/Events.hpp"
#include "../Events/EventManager.hpp"

#include <imgui_impl_glfw.h>



/* 
    ============ Callbacks
*/

static void error_callback(int error, const char* description)
{
    std::string es;

    switch (error) {
		case GLFW_NO_ERROR: es = "no error"; break;
		case GLFW_NOT_INITIALIZED: es = "not initialized"; break;
		case GLFW_NO_CURRENT_CONTEXT: es = "no current context"; break;
		case GLFW_INVALID_ENUM: es = "invalid enum"; break;
		case GLFW_INVALID_VALUE: es = "invalid value"; break;
		case GLFW_OUT_OF_MEMORY: es = "out of memory"; break;
		case GLFW_API_UNAVAILABLE: es = "api unavailable"; break;
		case GLFW_VERSION_UNAVAILABLE: es = "version unavailable"; break;
		case GLFW_PLATFORM_ERROR: es = "platform error"; break;
		case GLFW_FORMAT_UNAVAILABLE: es = "format unavailable"; break;
		case GLFW_NO_WINDOW_CONTEXT: es = "no window context"; break;
		default: es =  "unknown error"; break;
	}

    LOG_ERROR("GLFW error: {}\ndescription: {}", es, description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
	Window::width = width;
	Window::height = height;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_RELEASE){
        bool* keyStateWasChanged = (bool*)glfwGetWindowUserPointer(window);
        keyStateWasChanged[key] = true;
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    bool* keyStateWasChanged = (bool*)glfwGetWindowUserPointer(window);
    keyStateWasChanged[button] = true;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    EventManager::GetI().emplaceEvent<MouseScrolledEvent>((float)yoffset);
}

/* 
    ============ Window
*/

Window& Window::GetI()
{
    static Window instance;
    return instance;
}

void Window::Init(int width, int height)
{
    Window::width = width;
	Window::height = height;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        throw std::runtime_error("Couldn't initialize glfw");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    window = glfwCreateWindow(width, height, "kubiki", NULL, NULL);
    if (window==nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Couldn't create glfw window");
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(0);

    glViewport(0, 0, width, height);
    LOG_INFO("GL Version: {}", glGetString(GL_VERSION));

    glfwSetWindowSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

    for (int i=0; i<NUMBER_KEYS; i++){
        keyStateWasChanged[i] = false;
        keyPressedArray[i] = false;
    }
    glfwSetWindowUserPointer(window, (void*)keyStateWasChanged);

    double _x, _y;
    glfwGetCursorPos(window, &_x, &_y);
    curMouseX = (float)_x;
    curMouseY = (float)_y;

    guiMode = false;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::imguiInit()
{
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
}

Window::Window(){}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::PullEvents()
{
    glfwPollEvents();

    // Cursor pos
    double _x, _y;
    glfwGetCursorPos(window, &_x, &_y);
    float x = (float)_x;
    float y = (float)_y;

    if (x!=curMouseX || y!=curMouseY)
    {
        prevMouseX = curMouseX;
        prevMouseY = curMouseY;
        curMouseX = x;
        curMouseY = y;
        EventManager::GetI().emplaceEvent<MouseMovedEvent>(curMouseX-prevMouseX, curMouseY-prevMouseY);
    }

    // Keys
    float time = (float)glfwGetTime();
    for (int i=0; i<NUMBER_KEYS; i++)
    {
        if (keyStateWasChanged[i] && (!keyPressedArray[i])) // Press
        {
            keyPressedArray[i] = true;
            prevKeyPressTimeArray[i] = curKeyPressTimeArray[i];
            prevKeyReleaseTimeArray[i] = curKeyReleaseTimeArray[i];
            curKeyPressTimeArray[i] = time;

            if (i<NUMBER_MOUSE_BUTTONS){
                EventManager::GetI().emplaceEvent<MousePressedEvent>(i, 0.f);
            } else {
                EventManager::GetI().emplaceEvent<KeyPressedEvent>(i, 0.f);
            }
            keyStateWasChanged[i] = false;
        }
        else if (keyStateWasChanged[i] && keyPressedArray[i]) // Release
        {
            keyPressedArray[i] = false;
            curKeyReleaseTimeArray[i] = time;
            float duration = time - curKeyPressTimeArray[i];

            if (i<NUMBER_MOUSE_BUTTONS){
                EventManager::GetI().emplaceEvent<MouseReleasedEvent>(i, duration);
            } else {
                EventManager::GetI().emplaceEvent<KeyReleasedEvent>(i, duration);
            }
            keyStateWasChanged[i] = false;
        }
        else if (keyPressedArray[i]) // Hold
        {
            float duration = time - curKeyPressTimeArray[i];

            if (i<NUMBER_MOUSE_BUTTONS){
                EventManager::GetI().emplaceEvent<MousePressedEvent>(i, duration);
            } else {
                EventManager::GetI().emplaceEvent<KeyPressedEvent>(i, duration);
            }
        }
    }

}

void Window::switchGuiMode()
{
    if (guiMode){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    guiMode = !guiMode;
    
}

const std::string& Window::getKeyName(int keycode) const
{
    if (keycode<0 || keycode>=NUMBER_KEYS){
        return keyNameMap[NUMBER_KEYS];
    }
    return keyNameMap[keycode];
}
