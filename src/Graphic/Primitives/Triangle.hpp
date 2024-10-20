#pragma once
#include "stlh.hpp"
#include "logging.hpp"

#include "../Mesh/PrimitiveMesh.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class Triangle
{
public:
    PrimitiveMesh mesh;
    glm::vec3 P;
    
    Triangle();
    Triangle(glm::vec3 pos);
    ~Triangle();

    void build(glm::vec3 pos);
    void translate(glm::vec3 d);
};

inline Triangle::Triangle(): P(glm::vec3(0.0f))
{
    build(P);
}

inline Triangle::Triangle(glm::vec3 pos): P(pos)
{
    build(P);
}

inline Triangle::~Triangle(){}

inline void Triangle::build(glm::vec3 pos)
{
    mesh.vb.clear();
    mesh.vb.addVertex(glm::vec3(-0.6f, -0.4f, 0.0f) + pos, glm::vec3(1.f, 0.f, 0.f));
    mesh.vb.addVertex(glm::vec3(0.6f, -0.4f, 0.0f) + pos, glm::vec3(0.f, 1.f, 0.f));
    mesh.vb.addVertex(glm::vec3(0.f,  0.6f, 0.0f) + pos, glm::vec3(0.f, 0.f, 1.f));
    
    mesh.ib.clear();
    mesh.ib.addIndex(0);
    mesh.ib.addIndex(1);
    mesh.ib.addIndex(2);
}

inline void Triangle::translate(glm::vec3 d)
{
    P += d;
    build(P);
}