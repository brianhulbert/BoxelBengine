#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
	Camera();
	Camera(glm::mat4 projectionMat);
	~Camera() {};

	Transform& GetTransform();
	glm::mat4 GetView();
	glm::mat4 GetProj();

	void SetProj(glm::mat4 p) { proj = p; }

	Transform transform;
private:
	glm::mat4 proj;
};