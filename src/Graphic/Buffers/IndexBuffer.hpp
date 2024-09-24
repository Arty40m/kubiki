#pragma once
#include "stlh.hpp"
#include "../../DataStructures/DynamicBuffer.hpp"


#define _INDEX_BUFFER_INCREMENT 8

template<typename I>
class IndexBuffer: public DynamicBuffer
{
public:
    constexpr static uint32_t indexSize = sizeof(I);

    IndexBuffer();
    ~IndexBuffer();

    inline uint32_t size() const {return _size;}
    inline void clear() {_size = 0;}
    inline const void* getDataPtr() const {return data;}

    inline uint32_t sizeBytes() const {return _size*indexSize;}

    void addIndex(I idx);

private:
    uint32_t _size;
};

template<typename I>
IndexBuffer<I>::IndexBuffer(): _size(0)
{
    setIntIncrement(_INDEX_BUFFER_INCREMENT*indexSize);
}

template<typename I>
IndexBuffer<I>::~IndexBuffer(){}

template<typename I>
void IndexBuffer<I>::addIndex(I idx)
{
    if ((_size+1)*indexSize > _capacity){
        expandTo((_size+1)*indexSize);
    }
    I* idxPtr = (I*)(data + _size*indexSize);
    *idxPtr = idx;
    _size++;
}