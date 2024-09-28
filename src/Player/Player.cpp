#include "Player.hpp"
#include "logging.hpp"
#include <glm/ext/scalar_constants.hpp>



Player::Player(Camera* camera, glm::vec3 pos):
    camera(camera), 
    pos(pos), 
    height(1.75)
{
    setRotation(glm::pi<float>()/2.0f, 1.5f*glm::pi<float>());
    camera->setPos(pos + glm::vec3(0.0f, height, 0.0f));
}

Player::~Player(){}

void Player::setPos(const glm::vec3& v)
{
    pos = v;
    camera->setPos(pos + glm::vec3(0.0f, height, 0.0f));
}

void Player::setRotation(float p, float y)
{
    float pi = glm::pi<float>();

    int n = (int)(y / (2*pi+0.01f));
    n = (y>=0.0f) ? -n : (-n+1);
    yaw = y + (float)n * 2*pi;
    
    if (p < pitchClip){
        pitch = pitchClip;
    } else if (p > (pi - pitchClip)){
        pitch = (pi - pitchClip);
    } else {
        pitch = p;
    }

    float sin_pitch = std::sin(pitch);
    float cos_pitch = std::cos(pitch);
    float sin_yaw = std::sin(yaw);
    float cos_yaw = std::cos(yaw);

    glm::vec3 d = glm::vec3(-sin_pitch*sin_yaw, -cos_pitch, sin_pitch*cos_yaw);
    dir = glm::normalize(d);
    camera->setDir(dir);
}