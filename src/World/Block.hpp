#pragma once
#include "stlh.hpp"



class Block
{
public:
    Block(): type(0){}
    Block(uint16_t type): type(type){}

    ~Block(){};

private:
    uint16_t type;
};