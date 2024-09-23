#pragma once
#include "stlh.hpp"

#include "../Pipeline.hpp"
#include "../../Rendering/glBuffers.hpp"
#include "../../Mesh/BaseMesh.hpp"
#include "../../Vertices/BaseVertex.hpp"
#include "../../../Camera/Camera.hpp"


class PrimitivePipeline: public Pipeline
{
public:
    PrimitivePipeline();
    ~PrimitivePipeline();

    void render() override;
    void addMesh(Mesh* meshPtr);

    Camera* camera;

private:
    VAO vao;
    std::vector<Mesh*> meshPtrs;
    
};