#include "stl_headers.hpp"
#include "logging.hpp"

#include "Application.hpp"
#include "Window/Window.hpp"
#include "Events/Event.hpp"
#include "Events/Events.hpp"
#include "Events/EventManager.hpp"
#include "Window/KeyCodes.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"
#include <glm/vec3.hpp>



struct Vertex
{
    vec2 pos;
    vec3 col;
};
 
static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec2 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";


bool trCallback(Vertex* v, Event* e)
{
    if (!Window::GetI().isKeyPressed(LEFT_MOUSE_BUTTON)){
        return true;
    }

    MouseMovedEvent* E = (MouseMovedEvent*)e;
    float dx = E->dx;
    float dy = E->dy;

    for (int i=0; i<3; i++)
    {
        v[i].pos[0] = v[i].pos[0] + dx*0.01f;
        v[i].pos[1] = v[i].pos[1] - dy*0.01f;
    }
    return true;
}

int Application::run()
{
    Window::GetI().Init(640, 480);
    EventManager::GetI().Init();

    Vertex vertices[3] =
    {
        { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
        { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
        { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
    };

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), (void*) offsetof(Vertex, col));


    EventManager::GetI().addCallback(Event::EventType::MOUSE_MOVED_E, std::bind(trCallback, vertices, std::placeholders::_1));

    // EventManager::GetI().addCallback(Event::EventType::MOUSE_PRESSED_E, [](Event* e){
    //     LOG_INFO("{}", e->repr());
    //     return true;
    // });

    EventManager::GetI().addCallback(Event::EventType::MOUSE_RELEASED_E, [](Event* e){
        LOG_INFO("{}", e->repr());
        return true;
    });

    // EventManager::GetI().addCallback(Event::EventType::TEST_E, [](Event* e){
    //     LOG_INFO("TEST E created: {}", e->repr());
    //     return true;
    // });

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
        Window::GetI().clear();
        Window::GetI().PullEvents();
        EventManager::GetI().processEvents();

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        const float ratio = Window::GetI().getAspectRatio();
        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        // mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    exit(EXIT_SUCCESS);
}