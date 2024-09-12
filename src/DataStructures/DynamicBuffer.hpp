#pragma once
#include "../stl_headers.hpp"


class DynamicBuffer
{
public:
    DynamicBuffer(uint32_t initialSize, float increment);
    DynamicBuffer(uint32_t initialSize, uint32_t increment);
    ~DynamicBuffer() {delete[] data;}

    inline uint32_t capacity() const {return _capacity;};
    void resize(uint32_t n);

protected:
    std::byte* data;
    uint32_t _capacity;

    void expand();
    void expandTo(uint32_t needNbytes);

private:
    bool floatIncrement;
    float fIncrement;
    uint32_t iIncrement;
    
    inline void init(uint32_t initialSize) {data = new std::byte[initialSize];}
    uint32_t calculateCapacityAfterExpand(uint32_t N);
};


DynamicBuffer::DynamicBuffer(uint32_t initialSize, float increment):
    data(nullptr), _capacity(initialSize),
    floatIncrement(true), fIncrement(increment) 
{
    if (fIncrement<=1.0f){
        throw std::runtime_error("Invalid float increment (<= 1.0)");
    }
    init(initialSize);
}

DynamicBuffer::DynamicBuffer(uint32_t initialSize, uint32_t increment):
    data(nullptr), _capacity(initialSize),
    floatIncrement(false), iIncrement(increment)
{
    if (iIncrement<0){
        throw std::runtime_error("Invalid int increment (< 0)");
    }
    init(initialSize);
}

void DynamicBuffer::resize(uint32_t n)
{
    if (n==_capacity)
        return;

    std::byte* _data = new std::byte[n];
    int nBytesToCopy = (n>_capacity) ? _capacity : n;
    std::memcpy(_data, data, nBytesToCopy);

    delete[] data;
    data = _data;
    _capacity = n;
}

uint32_t DynamicBuffer::calculateCapacityAfterExpand(uint32_t N)
{
    if (floatIncrement){
        return (uint32_t)( (float)N * fIncrement );
    }else{
        return N + iIncrement;
    }
}

void DynamicBuffer::expand()
{
    uint32_t n = calculateCapacityAfterExpand(_capacity);
    resize(n);
}

void DynamicBuffer::expandTo(uint32_t needNbytes)
{
    uint32_t newCapacity = _capacity;
    while ((newCapacity - _capacity) < needNbytes){
        newCapacity = calculateCapacityAfterExpand(newCapacity);
    }
    resize(newCapacity);
}