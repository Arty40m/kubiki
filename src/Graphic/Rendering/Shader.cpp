#include "Shader.hpp"
#include "../../logging.hpp"


Shader::Shader(): shaderId(0){}

Shader::~Shader()
{
    off();
    glDeleteProgram(shaderId);
}

void Shader::Init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    shaderId = glCreateProgram();
    
    std::string vertexSource = readShader(vertexShaderPath);
    std::string fragmentSource = readShader(fragmentShaderPath);

    uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexSource);
    uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(shaderId, vs);
    glAttachShader(shaderId, fs);
    glLinkProgram(shaderId);
    glValidateProgram(shaderId);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

int Shader::getUniformLocation(const std::string& name)
{
    if (uniformLocationMap.find(name) != uniformLocationMap.end())
        return uniformLocationMap.at(name);

    int location = glGetUniformLocation(shaderId, name.c_str());
    uniformLocationMap.insert({name, location});
    return location;
}

std::string Shader::readShader(const std::string& shaderPath)
{
    std::ifstream file(shaderPath);

    if (!file.is_open()) {
        LOG_ERROR("Could not open shader file - {}", shaderPath);
        throw std::runtime_error("");
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    file.close();
    std::string src = ss.str();

    return src;
}

uint32_t Shader::compileShader(uint32_t shaderType, const std::string& src)
{
    uint32_t sid = glCreateShader(shaderType);
    const char* srcPtr = src.c_str();
    glShaderSource(sid, 1, &srcPtr, nullptr);
    glCompileShader(sid);

    int result;
    glGetShaderiv(sid, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &length);

        char* infoLog = new GLchar[length+1];
        infoLog[length] = 0;

        glGetShaderInfoLog(sid, length, nullptr, infoLog);
        LOG_ERROR("Failed to compile {} shader, error log:\n{}", 
                    (shaderType==GL_VERTEX_SHADER ? "vertex" : "fragment"), infoLog);
        delete[] infoLog;
        throw std::runtime_error("");
    }

    return sid;
}

// Uniforms

void Shader::setUniformMatrix4fv(const std::string& name, const float* data)
{
    int location = getUniformLocation(name);
    assert(location != -1);
    glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

void Shader::use() const
{
    if (shaderId==0){
        throw std::runtime_error("Can not use uninitialized shader");
    }
    glUseProgram(shaderId);
}

void Shader::off() const
{
    if (shaderId==0){
        throw std::runtime_error("Can not off uninitialized shader");
    }
    glUseProgram(0);
}