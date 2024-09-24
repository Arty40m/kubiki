#pragma once
#include "stlh.hpp"
#include "logging.hpp"

#include "../Mesh/BaseMesh.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class Cube
{
public:
    BaseMesh mesh;
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

void Cube::build(glm::vec3 pos)
{
    mesh.vb.clear();
    mesh.vb.addVertex(glm::vec3(-0.6f, -0.4f, 0.0f) + pos, glm::vec3(1.f, 0.f, 0.f));
    mesh.vb.addVertex(glm::vec3(0.6f, -0.4f, 0.0f) + pos, glm::vec3(0.f, 1.f, 0.f));
    mesh.vb.addVertex(glm::vec3(0.f,  0.6f, 0.0f) + pos, glm::vec3(0.f, 0.f, 1.f));
    mesh.modified = true;
}

void Cube::translate(glm::vec3 d)
{
    P += d;
    build(P);
}