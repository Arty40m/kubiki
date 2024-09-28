#pragma once
#include "stlh.hpp"

#include "../Pipeline.hpp"
#include "../../Rendering/glBuffers.hpp"
#include "../../Mesh/SkyBoxMesh.hpp"
#include "../../Vertices.hpp"
#include "../../Camera/Camera.hpp"


class SkyBoxPipeline: public Pipeline
{
public:
    SkyBoxPipeline();
    ~SkyBoxPipeline();

    void render() override;

    Camera* camera;

private:
    SkyBoxMesh mesh;
};