#pragma once
#include "stlh.hpp"


class DynamicBuffer
{
public:
    DynamicBuffer();
    ~DynamicBuffer() {delete[] data;}

    void setFloatIncrement(float increment);
    void setIntIncrement(uint32_t increment);
    inline uint32_t capacity() const {return _capacity;};
    virtual void resize(uint32_t n);

protected:
    std::byte* data;
    uint32_t _capacity;

    void expand();
    void expandTo(uint32_t needNbytes);

private:
    bool floatIncrement;
    float fIncrement;
    uint32_t iIncrement;

    uint32_t calculateCapacityAfterExpand(uint32_t N);
};