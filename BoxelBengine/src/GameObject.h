#pragma once

#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "scenes/Scene.h"
#include "Mesh.h"

class GameWindow;
class Texture;

struct Motion {
	glm::vec3 transVelocity;
	glm::vec3 rotVelocity;
};

class GameObject {
	//TODO: multitexture support
public:
	GameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile, VertexArray* va = nullptr, VertexBuffer* vb = nullptr, IndexBuffer* ib = nullptr);
	~GameObject();
	
	virtual void Update(float deltaTime);

	virtual void Draw();

	void Translate(glm::vec3 translation) { 
		transform.translation += translation; 
		updateTransformUniform = true;
	};
	void SetTranslation(glm::vec3 translation) { 
		transform.translation = translation;
		updateTransformUniform = true;
	};
	void Rotate(glm::vec3 rotation) { 
		transform.rotation += rotation; 
		updateTransformUniform = true;
	};
	void SetRotation(glm::vec3 rotation) {
		transform.rotation = rotation;
		updateTransformUniform = true;
	};

	void SetIndestructable();

	Transform transform;
	Motion velocity;
	std::string name;
	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Texture* texture;
	Mesh* mesh;
	Shader* shader;
	scene::Scene* parentScene;
private:
	Renderer renderer;
	bool updateTransformUniform;
	glm::mat4 GetModelMat();
	bool isDestructable;
protected:
	bool isVisible;
};