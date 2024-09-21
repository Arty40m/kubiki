#pragma once
#include "../../stl_headers.hpp"
#include "../../logging.hpp"
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>

#include "Pipeline.hpp"


class Renderer
{
public:
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    
    static Renderer& GetI();
    void Init();

    void clear();
    void render();
    void addPipeline(std::string&& name, Pipeline* p);
    Pipeline* getPipeline(std::string&& name);

private:
    std::vector<Pipeline*> pipelinePtrs;
    std::unordered_map<std::string, int> pipeNameIdxMap;

    Renderer();
    ~Renderer();
};