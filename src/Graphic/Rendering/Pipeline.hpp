#pragma once
#include "../../stl_headers.hpp"

#include "Renderer.hpp"
#include "Shader.hpp"
#include "../Mesh/Mesh.hpp"
#include "../glBuffers/VBO.hpp"
#include "../glBuffers/VAO.hpp"

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

    virtual void addMesh(Mesh* mp) = 0;
    virtual void render() = 0;

protected:
    std::vector<Mesh*> meshPtrs;
    std::vector<VBO> vbos;
    std::vector<VAO> vaos;

private:
    bool enabled;
};

inline Pipeline::Pipeline(){};

inline Pipeline::~Pipeline(){};
