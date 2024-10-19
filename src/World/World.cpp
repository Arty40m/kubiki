#include "World.hpp"
#include "logging.hpp"



World& World::GetI()
{
    static World instance;
    return instance;
}

void World::Init()
{
    dimsMap["overworld"] = new Dimension();
}

World::World(){}

World::~World(){}

Dimension* World::getDim(const char* name)
{
    if (dimsMap.find(name) == dimsMap.end()){
        std::string err = "Couldn't get dimension ' " + std::string(name) + "'";
        throw std::runtime_error(err);
    }

    return dimsMap.at(name);
}