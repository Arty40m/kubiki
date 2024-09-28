#pragma once
#include "stlh.hpp"

#include "../Pipeline.hpp"
#include "../../Rendering/glBuffers.hpp"
#include "../../Mesh/Mesh.hpp"
#include "../../Mesh/PrimitiveMesh.hpp"
#include "../../Vertices.hpp"
#include "../../Camera/Camera.hpp"


class PrimitivePipeline: public Pipeline
{
public:
    PrimitivePipeline();
    ~PrimitivePipeline();

    void render() override;
    void addMesh(Mesh* meshPtr);

    Camera* camera;

private:
    std::vector<Mesh*> meshPtrs;
    
};