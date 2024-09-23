#pragma once
#include "stlh.hpp"

#include "../Rendering/glBuffers.hpp"


class Mesh
{
public:
    bool modified;
    VBO* vbop;
    IBO* ibop;

    Mesh();
    ~Mesh();
};

inline Mesh::Mesh(): vbop(nullptr), ibop(nullptr){}

inline Mesh::~Mesh()
{
    if (vbop){
        delete vbop;
    }
    if (ibop){
        delete ibop;
    }
}
