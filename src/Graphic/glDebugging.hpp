#pragma once
#include "../stl_headers.hpp"
#include "../logging.hpp"
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>


#define GL_DEBUG

#ifdef GL_DEBUG
#define GLCall(f) glClearErrors();\
                    f;\
                    glLogError(#f, __FILE__, __LINE__);
#endif

#ifndef GL_DEBUG
#define GLCall(f) f;
#endif

static void glClearErrors(){while(glGetError() != GL_NO_ERROR);}
static void glLogError(const char* func, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::stringstream stream;
        stream << std::hex << error;
        std::string herror(stream.str());
        LOG_ERROR("GL error code (hex): {}; on function: {}; in file: {}; on line: {}", herror, func, file, line);
        throw std::runtime_error("");
    }
    
}