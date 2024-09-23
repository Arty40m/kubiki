#include "glBuffers.hpp"
#include "logging.hpp"



// Vertex buffer /////////////////////////////////////////////////////

VBO::VBO(): id(0), _size(0)
{
    glGenBuffers(1, &id);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &id);
}

void VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setStaticData(const void* data, uint32_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    _size = size;
}

// Index buffer /////////////////////////////////////////////////////

IBO::IBO(): id(0), _size(0)
{
    glGenBuffers(1, &id);
}

IBO::~IBO()
{
    glDeleteBuffers(1, &id);
}

void IBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IBO::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IBO::setStaticData(const void* data, uint32_t size)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    _size = size;
}

// Vertex array /////////////////////////////////////////////////////

VAO::VAO(): id(0)
{
    glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &id);
}

void VAO::bind() const {
    glBindVertexArray(id);
}

void VAO::unbind() const {
    glBindVertexArray(0);
}

void VAO::setFloatAttribute(uint32_t index, int size, int stride, int64_t offset)
{
    glBindVertexArray(id);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset) );
}