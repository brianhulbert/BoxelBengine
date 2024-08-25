#pragma once

class IndexBuffer {
private:
	unsigned int m_RendererID;
	
public:
	unsigned int m_Count;
	//should maybe support shorts for better porformance in the future
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
};