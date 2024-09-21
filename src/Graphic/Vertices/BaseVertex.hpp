#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


struct BaseVertex
{
    glm::vec3 pos;
    glm::vec3 col;

    BaseVertex(glm::vec3 pos, glm::vec3 col): pos(pos), col(col){}

    static void build(void* dataPtr, glm::vec3 pos, glm::vec3 col)
    {
        BaseVertex* v = new(dataPtr)BaseVertex(pos, col);
    }
};
