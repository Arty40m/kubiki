#pragma once
#include "stlh.hpp"
#include <glm/vec3.hpp>
#include "Chunk.hpp"
#include "../Graphic/Mesh/TerrainMesh.hpp"



class ChunksContainer
{
public:
    TerrainMesh mesh;

    ChunksContainer();
    ~ChunksContainer();

private:
    Chunk** chunksArray;
    uint32_t Nchunks;
    glm::ivec3 centerCoords;
};