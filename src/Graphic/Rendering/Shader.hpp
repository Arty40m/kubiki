#pragma once
#include "../../stl_headers.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>


class Shader
{
public:
    Shader();
    ~Shader();

    void Init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    inline uint32_t getId() const {return shaderId;}
    void use() const;
    void off() const;
    int getUniformLocation(const std::string& name);

    // Uniforms
    // void setUniform1i(const std::string& name, int data);
    // void setUniform1f(const std::string& name, float data);

    // void setUniformVector3fv(const std::string& name, const float* data);
    void setUniformMatrix4fv(const std::string& name, const float* data);

private:
    uint32_t shaderId;
    std::unordered_map<std::string, int> uniformLocationMap;

    std::string readShader(const std::string& shaderPath);
    uint32_t compileShader(uint32_t shaderType, const std::string& src);
    
};