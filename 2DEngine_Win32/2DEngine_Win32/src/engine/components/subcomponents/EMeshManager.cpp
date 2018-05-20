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

int EMeshManager::AddMesh(float* vertexData, int vertexCount, unsigned short* indices, int indicesCount)
{
	EMesh* mesh;
	mesh = new EMesh();
	mesh->Create(vertexData, vertexCount, indices, indicesCount);

	m_Meshes.push_back(mesh);

	return (int)m_Meshes.size() - 1;
}

void EMeshManager::FreeMeshes()
{
	for (unsigned i = 0; i < m_Meshes.size(); ++i)
	{
		m_Meshes[i]->Destroy();
		delete m_Meshes[i];
	}

	m_Meshes.clear();
}

EMesh* EMeshManager::GetMesh(unsigned index)
{
	if (index < m_Meshes.size())
		return m_Meshes[index];

	return 0;
}
