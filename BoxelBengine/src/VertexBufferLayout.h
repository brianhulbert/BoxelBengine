#pragma once

#include <vector>
#include <stdexcept>
#include <Renderer.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		//ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {};

  /*
	template<typename T>
	void Push(unsigned int count) {
		std::runtime_error("false");
	}

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	template<>
	void Push<glm::mat4>(unsigned int count) {
		for (unsigned int i = 0; i < count; i++) {
			for (int j = 0; j < 4; j++) {
				this-> Push<float>(4);
			}
		}
	}*/
  void push(unsigned int count) {
    std::runtime_error("false");
  }

  void push_float(unsigned int count) {
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
  }

  void push_uint(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
  }

  void push_uchar(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
  }

  void push_glmmat4(unsigned int count) {
		for (unsigned int i = 0; i < count; i++) {
			for (int j = 0; j < 4; j++) {
				this-> push_float(4);
			}
		}
  }

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};
