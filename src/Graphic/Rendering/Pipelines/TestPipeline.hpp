#pragma once
#include "../../../stl_headers.hpp"

#include "../../glDebugging.hpp"
#include "../Pipeline.hpp"
#include "../../Mesh/BaseMesh.hpp"
#include "../../Vertices/BaseVertex.hpp"


class TestPipeline: public Pipeline
{
public:
    
    TestPipeline();
    ~TestPipeline();

    void render() override;
    void addMesh(Mesh* mp) override;

private:
    
};

inline TestPipeline::TestPipeline():Pipeline()
{
};

inline TestPipeline::~TestPipeline()
{
};

inline void TestPipeline::addMesh(Mesh* mp)
{
    meshPtrs.push_back(mp);
    BaseMesh* meshPtr = (BaseMesh*)mp;
    
    VBO vbo;
    if (meshPtr->vb.size()){
        vbo.upload(meshPtr->vb.getDataPtr(), meshPtr->vb.sizeBytes());
    }
    vbos.push_back(vbo);

    VAO vao;
    vao.setFloatAttribute(0, 3, sizeof(BaseVertex), 0);
    vao.setFloatAttribute(1, 3, sizeof(BaseVertex), 3*sizeof(float));
    vaos.push_back(vao);
};

inline void TestPipeline::render()
{
    if (!isEnabled())
        return;

    shader.use();

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
        VBO& vbo = vbos[i];
        VAO& vao = vaos[i];

        vbo.bind();
        vao.bind();
        if (mp->modified){
            vbo.upload(mp->vb.getDataPtr(), mp->vb.sizeBytes());
            mp->modified = false;
        }

        GLCall(glDrawArrays(GL_TRIANGLES, 0, mp->vb.size()));
    }
};