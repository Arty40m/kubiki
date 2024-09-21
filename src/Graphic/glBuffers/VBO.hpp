#pragma once
#include "../../stl_headers.hpp"
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>

#include "../glDebugging.hpp"


class VBO
{
public:
    VBO();
    ~VBO();

    inline void bind() const {glBindBuffer(GL_ARRAY_BUFFER, id);}
    inline void unbind() const {glBindBuffer(GL_ARRAY_BUFFER, 0);}
    void glDelete();
    void upload(const void* data, uint32_t size);

private:
    uint32_t id;
};

inline VBO::VBO(): id(0)
{
    glGenBuffers(1, &id);
}

inline VBO::~VBO(){}

inline void VBO::glDelete()
{
    glDeleteBuffers(1, &id);
    id = 0;
}

inline void VBO::upload(const void* data, uint32_t size)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}