#include "PhysicsManager.hpp"
#include "logging.hpp"
#include <limits>
#include <glm/vec3.hpp>
#include <glm/ext.hpp>
#include "../Window/Window.hpp"



PhysicsManager& PhysicsManager::GetI()
{
    static PhysicsManager instance;
    return instance;
}

void PhysicsManager::Init(){}

PhysicsManager::PhysicsManager(){}

PhysicsManager::~PhysicsManager(){}

void PhysicsManager::movePlayer(Player* player, float dt)
{
    Player& pl = *player;
    pl.processStep(dt);
    auto& pcomp = pl.pcomp;

    glm::vec3 acceleration = pcomp.force/pcomp.mass;
    if (pl.isOnGround()) // Deacceleration
    {
        float vn = glm::length(pcomp.velocity);
        glm::vec3 da = (deacc * vn * pcomp.velocity)/pcomp.mass;
        da.y = 0.0f;
        acceleration -= da;
    }
    else // Gravity
    {
        acceleration.y -= 19.8f/pcomp.mass;
    }

    glm::vec3 plPos = pl.getPos();
    pcomp.velocity += 0.5f*dt*acceleration;
    
    if (glm::dot(pcomp.velocity, pcomp.velocity)>=velTh*velTh)
    {
        plPos = plPos + dt*pcomp.velocity;
        if (plPos.y<0.0f){
            plPos.y = 0.0f;
            pcomp.velocity.y = 0.0f;
        }
        pl.setPos(plPos);
    }

    pcomp.velocity += 0.5f*dt*acceleration;
}