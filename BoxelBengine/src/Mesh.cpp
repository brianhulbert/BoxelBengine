#include "Mesh.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include <memory>

Mesh::Mesh() : vertices(nullptr), vertexCount(0), indices(nullptr), indexCount(0) { }

Mesh::Mesh(float* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount, VertexBufferLayout* attribLayout) :
		vertices(vertices), vertexCount(vertexCount), indices(indices), indexCount(indexCount), vertexAttribs(attribLayout) { }

Mesh::~Mesh() {
	free(vertices);
	free(indices);
	delete vertexAttribs;
}

void Mesh::SetData(float* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount) {
	this->vertices = vertices;
	this->vertexCount = vertexCount;
	this->indices = indices;
	this->indexCount = indexCount;
}

void Mesh::SetDataLayout(VertexBufferLayout* vertexAttribs) {
	this->vertexAttribs = vertexAttribs;
}

unsigned int Mesh::GetVertexSize() { return vertexAttribs->GetStride(); }
