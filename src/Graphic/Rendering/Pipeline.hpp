#pragma once
#include "stlh.hpp"

#include "Shader.hpp"

#include <glm/vec3.hpp>
#include <glm/ext.hpp>


class Pipeline
{
public:
    Shader shader;

    Pipeline();
    ~Pipeline();

    inline bool isEnabled() const {return enabled;}
    inline void enable() {enabled = true;}
    inline void disable() {enabled = false;}
    virtual void render() = 0;

private:
    bool enabled;
};

inline Pipeline::Pipeline(){};

inline Pipeline::~Pipeline(){};
