//
//  2DEngine
//  EMeshManager.h
//  Eric Fleming
//  4/3/2018
//

#pragma once

#include <list>

#include "EMesh.h"

#define lilMeshManager EMeshManager::Instance()

class EMeshManager
{
public:
	// Returns only instance of mesh manager
	static EMeshManager* Instance();

	// Creates and adds mesh object to manager
	// Returns pointer to mesh
	// @ vertexData - vertex data of object packed in an array of 3 position and 2 texture coordinates per vertex
	// @ vertexCount - number of vertices multiplied by 5
	// @ indices - index data
	// @ indicesCount - size of indices array
	EMesh* AddMesh(float* vertexData, int vertexCount, unsigned short* indices, int indicesCount);

	// Frees all loaded meshes
	void FreeMeshes();

private:
	static EMeshManager* s_Instance;

	std::list<EMesh*> m_Meshes;

private:
	// Only one copy
	EMeshManager() {}
	~EMeshManager() {}
	EMeshManager(const EMeshManager& meshManager) {}
	void operator=(const EMeshManager& meshManager) {}
};

