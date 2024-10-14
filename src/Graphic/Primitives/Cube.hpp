#pragma once
#include "stlh.hpp"
#include "logging.hpp"

#include "../Mesh/PrimitiveMesh.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class Cube
{
public:
    PrimitiveMesh mesh;
    glm::vec3 P;
    
    Cube();
    Cube(glm::vec3 pos);
    ~Cube();

    void build(glm::vec3 pos);
    void translate(glm::vec3 d);
};

inline Cube::Cube(): P(glm::vec3(0.0f))
{
    build(P);
}

inline Cube::Cube(glm::vec3 pos): P(pos)
{
    build(P);
}

inline Cube::~Cube(){}

inline void Cube::build(glm::vec3 pos)
{
    mesh.vb.clear();
    mesh.vb.addVertex(glm::vec3(0.0f, 0.0f, 1.0f) + pos, glm::vec3(0.8f, 0.3f, 0.3f));
    mesh.vb.addVertex(glm::vec3(1.0f, 0.0f, 1.0f) + pos, glm::vec3(0.3f, 0.3f, 0.8f));
    mesh.vb.addVertex(glm::vec3(1.0f, 1.0f, 1.0f) + pos, glm::vec3(0.3f, 0.8f, 0.3f));
    mesh.vb.addVertex(glm::vec3(0.0f, 1.0f, 1.0f) + pos, glm::vec3(0.5f, 0.5f, 0.5f));

    mesh.vb.addVertex(glm::vec3(0.0f, 0.0f, 0.0f) + pos, glm::vec3(0.1f, 0.1f, 0.1f));
    mesh.vb.addVertex(glm::vec3(1.0f, 0.0f, 0.0f) + pos, glm::vec3(0.2f, 0.7f, 0.3f));
    mesh.vb.addVertex(glm::vec3(1.0f, 1.0f, 0.0f) + pos, glm::vec3(0.3f, 0.6f, 0.4f));
    mesh.vb.addVertex(glm::vec3(0.0f, 1.0f, 0.0f) + pos, glm::vec3(0.4f, 0.5f, 0.5f));
        
    mesh.ib.clear();
    // Z+
    mesh.ib.addIndex(0);
    mesh.ib.addIndex(1);
    mesh.ib.addIndex(2);
    mesh.ib.addIndex(0);
    mesh.ib.addIndex(2);
    mesh.ib.addIndex(3);
    
    // Z-
    mesh.ib.addIndex(5);
    mesh.ib.addIndex(4);
    mesh.ib.addIndex(7);
    mesh.ib.addIndex(5);
    mesh.ib.addIndex(7);
    mesh.ib.addIndex(6);
    
    // X+
    mesh.ib.addIndex(1);
    mesh.ib.addIndex(5);
    mesh.ib.addIndex(6);
    mesh.ib.addIndex(1);
    mesh.ib.addIndex(6);
    mesh.ib.addIndex(2);
    
    // X-
    mesh.ib.addIndex(4);
    mesh.ib.addIndex(0);
    mesh.ib.addIndex(3);
    mesh.ib.addIndex(4);
    mesh.ib.addIndex(3);
    mesh.ib.addIndex(7);
    
    // Y+
    mesh.ib.addIndex(3);
    mesh.ib.addIndex(2);
    mesh.ib.addIndex(6);
    mesh.ib.addIndex(3);
    mesh.ib.addIndex(6);
    mesh.ib.addIndex(7);
    
    // Y-
    mesh.ib.addIndex(4);
    mesh.ib.addIndex(5);
    mesh.ib.addIndex(1);
    mesh.ib.addIndex(4);
    mesh.ib.addIndex(1);
    mesh.ib.addIndex(0);
}

inline void Cube::translate(glm::vec3 d)
{
    P += d;
    build(P);
}