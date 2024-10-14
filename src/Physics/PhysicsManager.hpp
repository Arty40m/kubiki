#pragma once
#include "stlh.hpp"
#include "../Player/Player.hpp"



class PhysicsManager
{
public:
    float deacc = 1.0f;
    float velTh = 2.0f;

    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;
    
    static PhysicsManager& GetI();
    void Init();

    // void process();
    void movePlayer(Player* player, float dt);

private:
    PhysicsManager();
    ~PhysicsManager();
};