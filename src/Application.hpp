#pragma once
#include "stlh.hpp"
#include "Engine.hpp"

#include "Graphic/Graphic.hpp"
#include "Graphic/Camera/Camera.hpp"
#include "Player/Player.hpp"



class Application: public Engine
{
public:
    Application();
    ~Application();

    void onUpdate() override;

public:
    Camera camera;
    Player* player;

    SkyBoxPipeline* skyboxPipePtr;
    PrimitivePipeline* primitivePipePtr;

    std::vector<Cube> cubeVec;
};