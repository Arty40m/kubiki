#include "PrimitivePipeline.hpp"
#include "logging.hpp"
#include "../../../Window/Window.hpp"
#include "../../glDebugging.hpp"
#include "../../Rendering/glBuffers.hpp"



PrimitivePipeline::PrimitivePipeline(): Pipeline(){};

PrimitivePipeline::~PrimitivePipeline(){};

void PrimitivePipeline::addMesh(Mesh* meshPtr)
{
    BaseMesh* mp = (BaseMesh*)meshPtr;
    if (mp->vb.size()==0){
        throw std::runtime_error("Can not initialize gl buffer for empty mesh");    
    }
    meshPtrs.push_back(meshPtr);
    
    if (mp->vbop == nullptr)
    {
        mp->vbop = new VBO();
        // mp->ibop = new IBO();

        mp->vbop->setStaticData(mp->vb.getDataPtr(), mp->vb.sizeBytes());
        // mp->ibop->setStaticData(mp->ib.getDataPtr(), mp->ib.sizeBytes());

        vao.bind();
        vao.setFloatAttribute(0, 3, mp->vb.vertexSize, 0);
        vao.setFloatAttribute(1, 3, mp->vb.vertexSize, 3*sizeof(float));
    }
};

inline void PrimitivePipeline::render()
{
    if (!isEnabled())
        return;

    shader.use();
    vao.bind();

    glm::vec3 pos = {0.0f, 0.0f, 2.0f};
    glm::vec3 dirvec = {0.0f, 0.0f, -1.0f};
    glm::vec3 UP = {0.0f, 1.0f, 0.0f};

    float ratio = Window::GetI().getAspectRatio();
    glm::mat4 Projection = glm::perspective(glm::radians(120.0f), ratio, 0.01f, 100.0f);
    glm::mat4 View = glm::lookAt(pos, pos+dirvec, UP);
    glm::mat4 MVP = Projection*View;

    shader.setUniformMatrix4fv("MVP", (const GLfloat*) glm::value_ptr(MVP));

    for (int i=0; i<meshPtrs.size(); i++)
    {
        BaseMesh* mp = (BaseMesh*)meshPtrs[i];

        mp->vbop->bind();
        // mesh->ibo.bind();
        if (mp->modified){
            mp->vbop->setStaticData(mp->vb.getDataPtr(), mp->vb.sizeBytes());
            mp->modified = false;
        }

        GLCall(glDrawArrays(GL_TRIANGLES, 0, mp->vb.size()));
    }
};