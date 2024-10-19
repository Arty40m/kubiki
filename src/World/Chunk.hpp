#pragma once
#include "stlh.hpp"
#include "Block.hpp"



class Chunk
{
public:
    static const int Size = 16;

    Chunk();
    ~Chunk();

private:
    Block blocks[Size*Size*Size];
};