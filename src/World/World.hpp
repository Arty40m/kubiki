#pragma once
#include "stlh.hpp"
#include "ChunksContainer.hpp"



class Dimension;

class World
{
public:
    World(const World&) = delete;
    World& operator=(const World&) = delete;
    
    static World& GetI();
    void Init();

    Dimension* getDim(const char* name = "overworld");

private:
    World();
    ~World();

    std::unordered_map<std::string, Dimension*> dimsMap;
};

class Dimension: public ChunksContainer
{
public:
    Dimension(){};
    ~Dimension(){};
};