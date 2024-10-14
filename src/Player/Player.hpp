#pragma once
#include "stlh.hpp"
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include "Graphic/Camera/Camera.hpp"



struct PlayerMovementBuffer
{
    bool forward, back, right, left, jump, up, down;
    PlayerMovementBuffer(): 
        forward(false), back(false), 
        right(false), left(false),
        jump(false), up(false), down(false){}

    void reset()
    {
        forward = false;
        back = false;
        right = false;
        left = false;
        jump = false;
        up = false;
        down = false;
    }
};

struct PhysicsComponent
{
    glm::vec3 force, velocity, movement;
    float mass;
    bool isMoving;
    PhysicsComponent():
        force(glm::vec3(0.0f)),
        velocity(glm::vec3(0.0f)),
        movement(glm::vec3(0.0f)),
        mass(1.0f),
        isMoving(false){}
};

class Player
{
public:
    float jumpStrength = 125.0f;
    float jumpTime = 0.06f;
    float moveSpeed = 100.0f;


    const float pitchClip = glm::radians<float>(2.0f);
    PhysicsComponent pcomp;

    Player(Camera* camera, glm::vec3 pos);
    ~Player();

    inline glm::vec3 getPos() const {return pos;}
    void setPos(const glm::vec3& v);

    inline glm::vec3 getDir() const {return dir;} 
    std::pair<float, float> getRotation() const {return {pitch, yaw};}
    void setRotation(float p, float y);

    inline bool isOnGround() const {return (pos.y < 0.01f);}
    inline bool isJumping() const {return m_isJumping;}

    inline void stepForward() {moveBuffer.forward = true;}
    inline void stepBack() {moveBuffer.back = true;}
    inline void stepRight() {moveBuffer.right = true;}
    inline void stepLeft() {moveBuffer.left = true;}
    inline void jump() {moveBuffer.jump = true;}
    inline void moveUp() {moveBuffer.up = true;}
    inline void moveDown() {moveBuffer.down = true;}
    void processStep(float dt);
    inline void push(const glm::vec3& force) {pcomp.force += force;}

private:
    Camera* camera;
    glm::vec3 pos;
    float height;
    glm::vec3 dir;
    float pitch;
    float yaw;

    PlayerMovementBuffer moveBuffer;
    bool m_isJumping;
    float jumpCountdown;
};
