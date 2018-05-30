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

	// Creates a mesh object
	// @ vertexData - vertex data of object packed in an array of 3 position and 2 texture coordinates per vertex
	// @ vertexCount - number of vertices multiplied by 5
	// @ indices - index data
	// @ indicesCount - size of indices array
	void Create(float* vertexData, int vertexCount, unsigned short* indices, int indicesCount);

	// Frees buffers created to store mesh data
	void Destroy();

	// Draws the mesh object
	void Draw();

private:
	unsigned m_VAO;
	unsigned m_VBO;
	unsigned m_EBO;

	unsigned m_IndicesCount;

private:
	EMesh(const EMesh& mesh) {}
	void operator=(const EMesh& mesh) {}
};

