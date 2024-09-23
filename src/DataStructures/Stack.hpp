#pragma once
#include "stlh.hpp"
#include "DynamicBuffer.hpp"


class Stack: public DynamicBuffer
{
public:
    Stack();
    ~Stack();

    void resize(uint32_t n) override;
    inline uint32_t size() const {return (uint32_t)(ptr - data);};
    inline void clear() {ptr = data;};
    void* aloc(uint32_t n);

private:
    std::byte* ptr;
};