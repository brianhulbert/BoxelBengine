#include "Camera.h"

Camera::Camera() : transform({ glm::vec3(0.0f), glm::vec3(0.0f) }), proj(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)) { }
Camera::Camera(glm::mat4 projectionMat) : transform({ glm::vec3(0.0f), glm::vec3(0.0f) }), proj(projectionMat) { }

Transform& Camera::GetTransform() { return transform; }

glm::mat4 Camera::GetProj() { return proj; }

glm::mat4 Camera::GetView() {
    glm::mat4 transMat = glm::translate(glm::mat4(1.0f), -transform.translation);

    glm::mat4 xrot = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 yrot = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 zrot = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rotMat = zrot * yrot * xrot;

    return rotMat * transMat;
}