#include "ChunksContainer.hpp"
#include "logging.hpp"



ChunksContainer::ChunksContainer():
    chunksArray(nullptr),
    centerCoords({0,0,0})
{
    Nchunks = 8;
    chunksArray = new Chunk*[Nchunks];
    for (int i=0; i<Nchunks; i++){
        chunksArray[i] = nullptr;
    }
}

ChunksContainer::~ChunksContainer()
{
    for (int i=0; i<Nchunks; i++){
        delete chunksArray[i];
    }
    delete[] chunksArray;
}