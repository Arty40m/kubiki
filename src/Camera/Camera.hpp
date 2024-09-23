#pragma once
#include "stlh.hpp"
#include <glm/vec3.hpp>
#include <glm/ext.hpp>
// #include <glm/ext/matrix_float4x4.hpp>


class Camera
{
public:
    Camera();
    ~Camera();

    glm::mat4 getProjection();
    glm::mat4 getView();
    glm::mat4 getMVP();

// private:
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 upv;
    float yaw;
    float pitch;
    float nearPlane;
    float farPlane;
    float FOV;
};
