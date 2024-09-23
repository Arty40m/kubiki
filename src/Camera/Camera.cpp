#include "Camera.hpp"
#include "logging.hpp"
#include "../Window/Window.hpp"



Camera::Camera():
    pos(glm::vec3({0.0f, 0.0f, 2.0f})),
    dir(glm::vec3({0.0f, 0.0f, -1.0f})),
    upv(glm::vec3({0.0f, 1.0f, 0.0f})),
    yaw(1.5f * glm::pi<float>()),
    pitch(glm::pi<float>() / 2.0f),
    nearPlane(0.05f),
    farPlane(1000.0f),
    FOV(100.0f)
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::getProjection()
{
    float ratio = Window::GetI().getAspectRatio();
    return glm::perspective(glm::radians(FOV), ratio, nearPlane, farPlane);
}

glm::mat4 Camera::getView()
{
    return glm::lookAt(pos, pos+dir, upv);
}

glm::mat4 Camera::getMVP()
{
    return getProjection()*getView();
}
