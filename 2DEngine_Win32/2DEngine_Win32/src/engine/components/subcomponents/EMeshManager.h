//
//  2DEngine
//  EMeshManager.h
//  Eric Fleming
//  4/3/2018
//

#pragma once

#include <vector>

#include "EMesh.h"

#define lilMeshManager EMeshManager::Instance()

class EMeshManager
{
public:
	// Returns only instance of mesh manager
	static EMeshManager* Instance();

	int AddMesh(float* vertexData, int vertexCount, unsigned short* indices, int indicesCount);

	// Frees all loaded meshes
	void FreeMeshes();

	// Returns mesh at index or null if mesh dosen't exist
	EMesh* GetMesh(unsigned index);

	// Returns number of meshes in manager
	unsigned Size() { return (unsigned)m_Meshes.size(); }

private:
	static EMeshManager* s_Instance;

	std::vector<EMesh*> m_Meshes;

private:
	EMeshManager() {}
	~EMeshManager() {}
	EMeshManager(const EMeshManager& meshManager) {}
	void operator=(const EMeshManager& meshManager) {}
};

