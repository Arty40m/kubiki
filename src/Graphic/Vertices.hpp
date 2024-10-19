#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>



struct TerrainVertex
{
    glm::vec3 pos;
    glm::vec3 col;

    TerrainVertex(glm::vec3 pos, glm::vec3 col): pos(pos), col(col){}

    static void build(void* dataPtr, glm::vec3 pos, glm::vec3 col)
    {
        TerrainVertex* v = new(dataPtr)TerrainVertex(pos, col);
    }
};

struct PrimitiveVertex
{
    glm::vec3 pos;
    glm::vec3 col;

    PrimitiveVertex(glm::vec3 pos, glm::vec3 col): pos(pos), col(col){}

    static void build(void* dataPtr, glm::vec3 pos, glm::vec3 col)
    {
        PrimitiveVertex* v = new(dataPtr)PrimitiveVertex(pos, col);
    }
};

struct SkyBoxVertex
{
    glm::vec3 pos;

    SkyBoxVertex(glm::vec3 pos): pos(pos){}

    static void build(void* dataPtr, glm::vec3 pos)
    {
        SkyBoxVertex* v = new(dataPtr)SkyBoxVertex(pos);
    }
};
