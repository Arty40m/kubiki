#pragma once
#include "stlh.hpp"
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include "Graphic/Camera/Camera.hpp"



class Player
{
public:
    const float pitchClip = glm::radians<float>(2.0f);

    Player(Camera* camera, glm::vec3 pos);
    ~Player();

    inline glm::vec3 getPos() const {return pos;}
    void setPos(const glm::vec3& v);

    std::pair<float, float> getRotation() const {return {pitch, yaw};}
    void setRotation(float p, float y);

    inline glm::vec3 getDir() const {return dir;} 

private:
    Camera* camera;
    glm::vec3 pos;
    float height;
    glm::vec3 dir;
    float pitch;
    float yaw;
};
