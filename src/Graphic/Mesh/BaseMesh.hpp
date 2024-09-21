#pragma once
#include "Mesh.hpp"
#include "../Buffers/VertexBuffer.hpp"
#include "../Vertices/BaseVertex.hpp"


class BaseMesh: public Mesh
{
public:
    VertexBuffer<BaseVertex> vb;

    BaseMesh();
    ~BaseMesh();

private:
    
};

BaseMesh::BaseMesh()
{
}

BaseMesh::~BaseMesh()
{
}
