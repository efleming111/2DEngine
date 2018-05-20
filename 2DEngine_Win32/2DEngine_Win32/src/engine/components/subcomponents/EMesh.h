//
//  2DEngine
//  EMesh.h
//  Eric Fleming
//  4/3/2018
//

#pragma once

class EMesh
{
public:
	EMesh() {}
	~EMesh() {}

	void Create(float* vertexData, int vertexCount, unsigned short* indices, int indicesCount);
	void Destroy();

	void Draw();

	unsigned GetVAO() { return m_VAO; }

private:
	unsigned m_VAO;
	unsigned m_VBO;
	unsigned m_EBO;

	unsigned m_IndicesCount;

private:
	EMesh(const EMesh& mesh) {}
	void operator=(const EMesh& mesh) {}
};

