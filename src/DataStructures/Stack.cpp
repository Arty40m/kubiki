#include "DynamicBuffer.hpp"
#include "Stack.hpp"
#include "../logging.hpp"


Stack::Stack(): DynamicBuffer()
{
    ptr = data;
}

Stack::~Stack(){}

void Stack::resize(uint32_t n){
    uint32_t _size = size();
    DynamicBuffer::resize(n);
    ptr = data + _size;
}

void* Stack::aloc(uint32_t n)
{
    uint32_t _size = size();
    int needNbytes = (int)_size + n - _capacity;
    if (needNbytes>0){ // not enough memory
        LOG_DEBUG("Stack aloc: cur cap: {}; lacks: {}", _capacity, needNbytes);
        expandTo(needNbytes);
        ptr = data + _size;
    }
    void* p = (void*)ptr;
    ptr += n;
    return p;
}