#pragma once
#include "stlh.hpp"
#include <glad/glad.h>


// Vertex buffer /////////////////////////////////////////////////////

class VBO
{
public:
    VBO();
    ~VBO();

    void bind() const;
    void unbind() const;
    inline uint32_t size() const {return _size;}
    void setStaticData(const void* data, uint32_t size);

// private:
    uint32_t id;
    uint32_t _size;
};

// Index buffer /////////////////////////////////////////////////////

class IBO
{
public:
    IBO();
    ~IBO();

    void bind() const;
    void unbind() const;
    inline uint32_t size() const {return _size;}
    void setStaticData(const void* data, uint32_t size);

// private:
    uint32_t id;
    uint32_t _size;
};

// Vertex array /////////////////////////////////////////////////////

class VAO
{
public:
    VAO();
    ~VAO();

    void bind() const;
    void unbind() const;
    void setFloatAttribute(uint32_t index, int size, int stride, int64_t offset);

// private:
    uint32_t id;
};