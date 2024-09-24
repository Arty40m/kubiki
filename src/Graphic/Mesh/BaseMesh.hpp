#pragma once
#include "Mesh.hpp"
#include "../Buffers/VertexBuffer.hpp"
#include "../Buffers/IndexBuffer.hpp"
#include "../Vertices/BaseVertex.hpp"


class BaseMesh: public Mesh
{
public:
    VertexBuffer<BaseVertex> vb;
    IndexBuffer<uint32_t> ib;

    BaseMesh();
    ~BaseMesh();

private:
    
};

inline BaseMesh::BaseMesh(): Mesh()
{
}

inline BaseMesh::~BaseMesh()
{
}