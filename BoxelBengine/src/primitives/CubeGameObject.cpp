#include "CubeGameObject.h"
#include <cstring>

CubeGameObject::CubeGameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile) :
	GameObject(parentScene, mesh, shaderfile, texturefile) {
	name = "Cube";
}

CubeGameObject* CubeGameObject::CreateCube(scene::Scene* parentScene, float scale) {
	float vertices[] = {
		//front face
		-0.5f * scale, -0.5f * scale, -0.5f * scale,	0.0f, 0.0f,
		 0.5f * scale, -0.5f * scale, -0.5f * scale,	1.0f, 0.0f,
		 0.5f * scale,  0.5f * scale, -0.5f * scale,	1.0f, 1.0f,
		-0.5f * scale,  0.5f * scale, -0.5f * scale,	0.0f, 1.0f,

		//right face
		 0.5f * scale, -0.5f * scale, -0.5f * scale,	0.0f, 0.0f,
		 0.5f * scale, -0.5f * scale,  0.5f * scale,	1.0f, 0.0f,
		 0.5f * scale,  0.5f * scale,  0.5f * scale,	1.0f, 1.0f,
		 0.5f * scale,  0.5f * scale, -0.5f * scale,	0.0f, 1.0f,

		//back face
		 0.5f * scale, -0.5f * scale,  0.5f * scale,	0.0f, 0.0f,
		-0.5f * scale, -0.5f * scale,  0.5f * scale,	1.0f, 0.0f,
		-0.5f * scale,  0.5f * scale,  0.5f * scale,	1.0f, 1.0f,
		 0.5f * scale,  0.5f * scale,  0.5f * scale,	0.0f, 1.0f,

		//left face
		-0.5f * scale, -0.5f * scale,  0.5f * scale,	0.0f, 0.0f,
		-0.5f * scale, -0.5f * scale, -0.5f * scale,	1.0f, 0.0f,
		-0.5f * scale,  0.5f * scale, -0.5f * scale,	1.0f, 1.0f,
		-0.5f * scale,  0.5f * scale,  0.5f * scale,	0.0f, 1.0f,

		//top face
		-0.5f * scale,  0.5f * scale, -0.5f * scale,	0.0f, 0.0f,
		 0.5f * scale,  0.5f * scale, -0.5f * scale,	1.0f, 0.0f,
		 0.5f * scale,  0.5f * scale,  0.5f * scale,	1.0f, 1.0f,
		-0.5f * scale,  0.5f * scale,  0.5f * scale,	0.0f, 1.0f,

		//bottom face
		-0.5f * scale, -0.5f * scale,  0.5f * scale,	0.0f, 0.0f,
		 0.5f * scale, -0.5f * scale,  0.5f * scale,	1.0f, 0.0f,
		 0.5f * scale, -0.5f * scale, -0.5f * scale,	1.0f, 1.0f,
		-0.5f * scale, -0.5f * scale, -0.5f * scale,	0.0f, 1.0f
	};
	unsigned int indices[] = {
		//front face
		 0,  1,  2,
		 2,  3,  0,

		//right face
		 4,  5,  6,
		 6,  7,  4,

		//back face
		 8,  9, 10,
		10, 11,  8,

		//left face
		12, 13, 14,
		14, 15, 12,

		//top face
		16, 17, 18,
		18, 19, 16,

		//bottom face
		20, 21, 22,
		22, 23, 20
	};

	//create vertex buffer
	unsigned int vertexBufferSize = 4 * 5 * 6 * sizeof(float);
	float* vertexBuffer = (float*)malloc(vertexBufferSize);
	std::memcpy(vertexBuffer, vertices, vertexBufferSize);

	//Specify the layout of the buffer
	VertexBufferLayout* vertexLayout = new VertexBufferLayout();
	vertexLayout->push_float(3);
	vertexLayout->push_float(2);

	//create index buffer
	unsigned int indexBufferSize = 6 * 6 * sizeof(unsigned int);
	unsigned int* indexBuffer = (unsigned int*)malloc(indexBufferSize);
	std::memcpy(indexBuffer, indices, indexBufferSize);

	//Create a mesh object for the cube
	Mesh* cubeMesh = new Mesh(vertexBuffer, vertexBufferSize / sizeof(float), indexBuffer, indexBufferSize / sizeof(unsigned int), vertexLayout);
	
	return new CubeGameObject(parentScene, cubeMesh, "res/shaders/BasicLighting.shader", "res/textures/cat2.png");
}
