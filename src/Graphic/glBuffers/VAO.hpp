#pragma once
#include "../../stl_headers.hpp"
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>

#include "../glDebugging.hpp"


class VAO
{
public:
    VAO();
    ~VAO();

    inline void bind() const {glBindVertexArray(id);}
    inline void unbind() const {glBindVertexArray(0);}
    void glDelete();
    void setFloatAttribute(uint32_t index, int size, int stride, int64_t offset);

private:
    uint32_t id;
};

inline VAO::VAO(): id(0)
{
    glGenVertexArrays(1, &id);
}

inline VAO::~VAO(){}

inline void VAO::glDelete()
{
    glDeleteBuffers(1, &id);
    id = 0;
}

inline void VAO::setFloatAttribute(uint32_t index, int size, int stride, int64_t offset)
{
    bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset) );
}