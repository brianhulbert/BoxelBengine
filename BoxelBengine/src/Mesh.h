class VertexBufferLayout;

class Mesh {
public:
	Mesh();
	Mesh(float* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount, VertexBufferLayout* attribLayout);
	~Mesh();
	
	void SetDataLayout(VertexBufferLayout* vertexAttribs);
	void SetData(float* vertices, unsigned int VertexCount, unsigned int* indices, unsigned int indexCount);

	float* GetVertexData() { return vertices; }
	unsigned int GetVertexCount() { return vertexCount; }
	unsigned int* GetIndexData() { return indices; }
	unsigned int GetIndexCount() { return indexCount; }
	VertexBufferLayout* GetVertexLayout() { return vertexAttribs; };
	unsigned int GetVertexSize();
private:
	float* vertices;
	unsigned int vertexCount;
	unsigned int* indices;
	unsigned int indexCount;
	VertexBufferLayout* vertexAttribs;
};