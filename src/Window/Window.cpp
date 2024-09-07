#include "../stl_headers.hpp"
#include "../logging.hpp"
#include "Window.hpp"


static void error_callback(int error, const char* description) {
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
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
	Window::width = width;
	Window::height = height;
}


Window& Window::GetInstance()
{
    static Window instance;
    return instance;
}

void Window::_Init(int width, int height)
{
    Window::width = width;
	Window::height = height;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        throw std::runtime_error("Couldn't initialize glfw");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    // glfwSetCursorPosCallback(window, mouse_callback);
	// glfwSetScrollCallback(window, scroll_callback);
	// glfwSetMouseButtonCallback(window, mouse_button_callback);

}

Window::Window(){}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::_PullEvents()
{
    glfwPollEvents();

    // Create input events
}

void Window::_clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}