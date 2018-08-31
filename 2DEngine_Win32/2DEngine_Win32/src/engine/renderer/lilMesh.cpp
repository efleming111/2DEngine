//
//  2DEngine
//  lilMesh.cpp
//  Eric Fleming
//  4/3/2018
//

#include "../../../thirdpartysrc/glad/glad/glad.h"
#include <SDL.h>

#include "lilMesh.h"

void lilMesh::Create(float* vertexData, int vertexCount, unsigned short* indices, int indicesCount)
{
	mIndicesCount = indicesCount;

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indicesCount, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void lilMesh::Destroy()
{
	glDeleteBuffers(1, &mEBO);
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void lilMesh::Draw()
{
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_SHORT, 0);
}
