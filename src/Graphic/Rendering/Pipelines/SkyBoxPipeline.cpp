#include "SkyBoxPipeline.hpp"
#include "logging.hpp"
#include "../../../Window/Window.hpp"
#include "../../glDebugging.hpp"
#include "../../Rendering/glBuffers.hpp"



SkyBoxPipeline::SkyBoxPipeline()
{
    mesh.vaop = new VAO();
    mesh.vbop = new VBO();
    mesh.ibop = new IBO();

    mesh.vbop->setStaticData(mesh.vb.getDataPtr(), mesh.vb.sizeBytes());
    mesh.ibop->setStaticData(mesh.ib.getDataPtr(), mesh.ib.sizeBytes());

    mesh.vaop->setFloatAttribute(0, 3, mesh.vb.vertexSize, 0);
}

SkyBoxPipeline::~SkyBoxPipeline(){}

void SkyBoxPipeline::render()
{
    if (!isEnabled())
        return;

    shader.use();
    glEnable(GL_DEPTH_TEST);

    glm::mat4 MVP = camera->getMVP();
    shader.setUniformMatrix4fv("MVP", (const GLfloat*) glm::value_ptr(MVP));
    shader.setUniformVector3fv("dir", (const GLfloat*) glm::value_ptr(camera->getDir()));
    // shader.setUniform1f("boxSize", mesh.boxSize);

    mesh.vaop->bind();
    mesh.vbop->bind();
    mesh.ibop->bind();
    if (mesh.modified)
    {
        mesh.vaop->setFloatAttribute(0, 3, mesh.vb.vertexSize, 0);
        mesh.modified = false;
    }

    GLCall(glDrawElements(GL_TRIANGLES, mesh.ib.size(), GL_UNSIGNED_INT, nullptr););
}