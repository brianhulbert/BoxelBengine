#include "TriangleGameObject.h"
#include <cstring>

TriangleGameObject::TriangleGameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile) :
	GameObject(parentScene, mesh, shaderfile, texturefile) {
	name = "Triangle";
}

TriangleGameObject* TriangleGameObject::CreateTriangle(scene::Scene* parentScene, float scale) {
	float vertices[] = {
		//face 1
		-0.5f, -0.54006f, -0.866f,	0.0f, 0.0f,
		 1.0f, -0.54006f,  0.0f,	1.0f, 0.0f,
		 0.0f,  1.08012f,  0.0f,	0.0f, 1.0f,
		-0.5f, -0.54006f,  0.866f,	1.0f, 1.0f,

		 //face 2
		 -0.5f, -0.54006f,  0.866f,	0.0f, 1.0f,
		  1.0f, -0.54006f,  0.0f,	0.0f, 0.0f,
		 -0.5f, -0.54006f, -0.866f,	1.0f, 0.0f,
		  0.0f,  1.08012f,  0.0f,	1.0f, 1.0f
	};

	unsigned int indices[] = {
		//face 1
		0, 1, 2,
		1, 3, 2,

		//face 2
		4, 5, 6,
		4, 6, 7
	};

	//create vertex buffer
	unsigned int vertexBufferSize = 2 * 4 * 5 * sizeof(float);
	float* vertexBuffer = (float*)malloc(vertexBufferSize);
	std::memcpy(vertexBuffer, vertices, vertexBufferSize);

	//Specify the layout of the buffer
	VertexBufferLayout* vertexLayout = new VertexBufferLayout();
	vertexLayout->push_float(3);
	vertexLayout->push_float(2);

	//create index buffer
	unsigned int indexBufferSize = 6 * 2 * sizeof(unsigned int);
	unsigned int* indexBuffer = (unsigned int*)malloc(indexBufferSize);
	std::memcpy(indexBuffer, indices, indexBufferSize);

	//Create a mesh object for the cube
	Mesh* triangleMesh = new Mesh(vertexBuffer, vertexBufferSize / sizeof(float), indexBuffer, indexBufferSize / sizeof(unsigned int), vertexLayout);

	return new TriangleGameObject(parentScene, triangleMesh, "res/shaders/Basic3D.shader", "res/textures/cat.png");
}
