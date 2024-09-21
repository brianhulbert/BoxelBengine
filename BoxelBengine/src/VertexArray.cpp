#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <iostream>

#define INT2VOIDP(i) ((void*)(uintptr_t)(i))

VertexArray::VertexArray() : attribCount(0){
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
	GLCALL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, unsigned int divisor) {
	this->Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(i + attribCount));
		GLCALL(glVertexAttribPointer(i + attribCount, element.count, element.type, element.normalized, layout.GetStride(), INT2VOIDP(offset)));
		GLCALL(glVertexAttribDivisor(i + attribCount, divisor));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	attribCount += elements.size();
}

void VertexArray::Bind() const {
	GLCALL(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const {
	GLCALL(glBindVertexArray(0));
}
