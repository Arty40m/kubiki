#include "Renderer.hpp"
#include "../../logging.hpp"



static void APIENTRY glDebugCallback(GLenum source,
                                    GLenum type, 
                                    unsigned int id, 
                                    GLenum severity, 
                                    GLsizei length, 
                                    const char *message, 
                                    const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::string sourceString;
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             sourceString = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceString = "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceString = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceString = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     sourceString = "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           sourceString = "Other"; break;
    }

    std::string typeString;
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               typeString = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeString = "Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeString = "Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         typeString = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         typeString = "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              typeString = "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          typeString = "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           typeString = "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               typeString = "Other"; break;
    }
    
    std::string severityString;
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         severityString = "high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severityString = "medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          severityString = "low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityString = "notification"; break;
    }
    LOG_ERROR("GL error id {}; source: {}; type: {}; severity: {}\n---Message: {}\n", 
                id, sourceString, typeString, severityString, message);
}

Renderer& Renderer::GetI()
{
    static Renderer instance;
    return instance;
}

void Renderer::Init()
{
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
        glDebugMessageCallback(glDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    } else {
        LOG_WARN("Couldn't set gl debug callback");
    }
}

Renderer::Renderer(){}

Renderer::~Renderer()
{
    for (int i=0; i<pipelinePtrs.size(); i++){
        delete pipelinePtrs[i];
    }
}

void Renderer::clear()
{
    glClearColor(0.2f, 0.5f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render()
{
    for (int i=0; i<pipelinePtrs.size(); i++){
        Pipeline* p = pipelinePtrs[i];
        p->render();
    }
}

void Renderer::addPipeline(std::string&& name, Pipeline* p)
{
    if (pipeNameIdxMap.find(name)!=pipeNameIdxMap.end()){
        std::string err = "Pipeline " + name + " is already registered";
        throw std::runtime_error(err);
    }

    pipeNameIdxMap.insert({name, pipelinePtrs.size()});
    pipelinePtrs.push_back(p);
}

Pipeline* Renderer::getPipeline(std::string&& name)
{
    if (pipeNameIdxMap.find(name)==pipeNameIdxMap.end()){
        return nullptr;
    }
    return pipelinePtrs[pipeNameIdxMap.at(name)];
}