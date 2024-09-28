#pragma once
#include "stlh.hpp"
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>



class Camera
{
public:
    Camera();
    ~Camera();

    inline glm::vec3 getPos() const {return pos;}
    inline void setPos(const glm::vec3& v) {pos = v;}

    inline glm::vec3 getDir() const {return dir;}
    inline void setDir(const glm::vec3& v) {dir = v;}

    inline float getFOV() const {return FOV;}
    inline void setFOV(float fov) {FOV = fov;}

    glm::mat4 getProjection();
    glm::mat4 getView();
    glm::mat4 getMVP();

private:
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 upv;
    float nearPlane;
    float farPlane;
    float FOV;
};
