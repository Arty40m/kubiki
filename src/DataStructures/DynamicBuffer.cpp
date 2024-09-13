#include "DynamicBuffer.hpp"
#include "../logging.hpp"


DynamicBuffer::DynamicBuffer(): 
    data(nullptr), 
    floatIncrement(true), 
    fIncrement(2.0f)
{
    data = new std::byte[32];
    _capacity = 32;
    setFloatIncrement(2.f);
}

void DynamicBuffer::setFloatIncrement(float increment)
{
    if (increment<=1.0f){
        throw std::runtime_error("Invalid float increment (<= 1.0)");
    }
    floatIncrement = true;
    fIncrement = increment;
}

void DynamicBuffer::setIntIncrement(uint32_t increment)
{
    if (increment<0){
        throw std::runtime_error("Invalid int increment (< 0)");
    }
    iIncrement = false;
    iIncrement = increment;
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