//
//  2DEngine
//  EMeshManager.h
//  Eric Fleming
//  4/3/2018
//

#include "EMeshManager.h"

EMeshManager* EMeshManager::s_Instance = 0;

EMeshManager* EMeshManager::Instance()
{
	if (!s_Instance)
		s_Instance = new EMeshManager();

	return s_Instance;
}

EMesh* EMeshManager::AddMesh(float* vertexData, int vertexCount, unsigned short* indices, int indicesCount)
{
	EMesh* mesh;
	mesh = new EMesh();
	mesh->Create(vertexData, vertexCount, indices, indicesCount);

	m_Meshes.push_back(mesh);

	return mesh;
}

void EMeshManager::FreeMeshes()
{
	for (std::list<EMesh*>::iterator it = m_Meshes.begin(); it != m_Meshes.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	m_Meshes.clear();
}

