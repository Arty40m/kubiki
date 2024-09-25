#pragma once
#include "Mesh.hpp"
#include "../Buffers/VertexBuffer.hpp"
#include "../Buffers/IndexBuffer.hpp"
#include "../Vertices.hpp"



class PrimitiveMesh: public Mesh
{
public:
    VertexBuffer<PrimitiveVertex> vb;
    IndexBuffer<uint32_t> ib;

    PrimitiveMesh();
    ~PrimitiveMesh();

private:
    
};

inline PrimitiveMesh::PrimitiveMesh(): Mesh()
{
}

inline PrimitiveMesh::~PrimitiveMesh()
{
}