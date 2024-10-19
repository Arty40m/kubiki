#include "Chunk.hpp"
#include "logging.hpp"



Chunk::Chunk()
{
    for (int x=0; x<Size; x++){
        for (int z=0; z<Size; z++){
            int idx = Size*z + x;
            blocks[idx] = Block(1);
        }
    }
}

Chunk::~Chunk()
{
}
