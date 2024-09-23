#pragma once
#include "stlh.hpp"
#include "../../DataStructures/DynamicBuffer.hpp"


#define _VERTEX_BUFFER_INCREMENT 8

template<typename V>
class VertexBuffer: public DynamicBuffer
{
public:
    constexpr static uint32_t vertexSize = sizeof(V);

    VertexBuffer();
    ~VertexBuffer();

    inline uint32_t size() const {return _size;}
    inline void clear() {_size = 0;}
    inline const void* getDataPtr() const {return data;}

    inline uint32_t sizeBytes() const {return _size*vertexSize;}

    template<typename... Types>
    void addVertex(Types&& ... args);

private:
    uint32_t _size;
};

template<typename V>
VertexBuffer<V>::VertexBuffer(): _size(0)
{
    setIntIncrement(_VERTEX_BUFFER_INCREMENT*vertexSize);
}

template<typename V>
VertexBuffer<V>::~VertexBuffer()
{
}

template<typename V>
template<typename... Types>
void VertexBuffer<V>::addVertex(Types&& ... args)
{
    if ((_size+1)*vertexSize > _capacity){
        expandTo((_size+1)*vertexSize);
    }
    V::build((data + _size*vertexSize), std::forward<Types>(args)...);
    _size++;
}