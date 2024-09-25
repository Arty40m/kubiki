#pragma once
#include "Mesh.hpp"
#include "../Buffers/VertexBuffer.hpp"
#include "../Buffers/IndexBuffer.hpp"
#include "../Vertices.hpp"



class SkyBoxMesh: public Mesh
{
public:
    float boxSize;
    VertexBuffer<SkyBoxVertex> vb;
    IndexBuffer<uint32_t> ib;

    SkyBoxMesh();
    ~SkyBoxMesh();  
};

inline SkyBoxMesh::SkyBoxMesh(): Mesh(), boxSize(100.0f)
{
    glm::vec3 shift = {boxSize/2, boxSize/2, boxSize/2};

    vb.clear();
    vb.addVertex(boxSize * glm::vec3(0.0f, 0.0f, 1.0f) - shift);
    vb.addVertex(boxSize * glm::vec3(1.0f, 0.0f, 1.0f) - shift);
    vb.addVertex(boxSize * glm::vec3(1.0f, 1.0f, 1.0f) - shift);
    vb.addVertex(boxSize * glm::vec3(0.0f, 1.0f, 1.0f) - shift);

    vb.addVertex(boxSize * glm::vec3(0.0f, 0.0f, 0.0f) - shift);
    vb.addVertex(boxSize * glm::vec3(1.0f, 0.0f, 0.0f) - shift);
    vb.addVertex(boxSize * glm::vec3(1.0f, 1.0f, 0.0f) - shift);
    vb.addVertex(boxSize * glm::vec3(0.0f, 1.0f, 0.0f) - shift);
        
    ib.clear();
    // Z+
    ib.addIndex(0);
    ib.addIndex(1);
    ib.addIndex(2);
    ib.addIndex(0);
    ib.addIndex(2);
    ib.addIndex(3);
    
    // Z-
    ib.addIndex(5);
    ib.addIndex(4);
    ib.addIndex(7);
    ib.addIndex(5);
    ib.addIndex(7);
    ib.addIndex(6);
    
    // X+
    ib.addIndex(1);
    ib.addIndex(5);
    ib.addIndex(6);
    ib.addIndex(1);
    ib.addIndex(6);
    ib.addIndex(2);
    
    // X-
    ib.addIndex(4);
    ib.addIndex(0);
    ib.addIndex(3);
    ib.addIndex(4);
    ib.addIndex(3);
    ib.addIndex(7);
    
    // Y+
    ib.addIndex(3);
    ib.addIndex(2);
    ib.addIndex(6);
    ib.addIndex(3);
    ib.addIndex(6);
    ib.addIndex(7);
    
    // Y-
    ib.addIndex(4);
    ib.addIndex(5);
    ib.addIndex(1);
    ib.addIndex(4);
    ib.addIndex(1);
    ib.addIndex(0);
    
    modified = true;
}

inline SkyBoxMesh::~SkyBoxMesh()
{
}