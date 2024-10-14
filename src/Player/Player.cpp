#include "Player.hpp"
#include "logging.hpp"
#include <glm/ext/scalar_constants.hpp>
#include "../Window/Window.hpp"



Player::Player(Camera* camera, glm::vec3 pos):
    camera(camera), 
    pos(pos), 
    height(1.75),
    m_isJumping(false),
    jumpCountdown(0.0f)
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
    static const float pi = glm::pi<float>();

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

void Player::processStep(float dt)
{
    glm::vec3 movement(0.0f);

    if (moveBuffer.forward || moveBuffer.back)
    {
        float sign = (moveBuffer.forward) ? 1.0f : -1.0f;
        movement += sign*glm::normalize(glm::vec3(dir.x, 0.0f, dir.z));
    }
    if (moveBuffer.right || moveBuffer.left)
    {
        float sign = (moveBuffer.right) ? 1.0f : -1.0f;
        glm::vec3 right = glm::normalize(glm::cross(dir, {0.0f, 1.0f, 0.0f}));
        movement += sign*right;
    }

    if (movement.x!=0.0f || movement.y!=0.0f || movement.z!=0.0f){
        movement = moveSpeed*glm::normalize(movement);
    }
    
    if (moveBuffer.jump && !m_isJumping)
    {
        m_isJumping = true;
        jumpCountdown = jumpTime + dt;
    }

    if (m_isJumping)
    {
        jumpCountdown -= dt;
        if (jumpCountdown>0.0f){ // Still in jump
            movement += jumpStrength*glm::vec3(0.0f, 1.0f, 0.0f);
        } else {
            m_isJumping = false;
        }
    }

    pcomp.force = movement;
    moveBuffer.reset();
}