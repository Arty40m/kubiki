#pragma once
#include "Mesh.hpp"
#include "../Buffers/VertexBuffer.hpp"
#include "../Buffers/IndexBuffer.hpp"
#include "../Vertices.hpp"



class TerrainMesh: public Mesh
{
public:
    VertexBuffer<TerrainVertex> vb;
    IndexBuffer<uint32_t> ib;

    TerrainMesh();
    ~TerrainMesh();

private:
    
};

inline TerrainMesh::TerrainMesh(): Mesh()
{
}

inline TerrainMesh::~TerrainMesh()
{
}