//
//  2DEngine
//  EGameObjectManager.h
//  Eric Fleming
//  5/24/2018
//

#include "EGameObjectManager.h"

EGameObjectManager* EGameObjectManager::s_Instance = 0;

EGameObjectManager* EGameObjectManager::Instance()
{
	if (!s_Instance)
		s_Instance = new EGameObjectManager();

	return s_Instance;
}

void EGameObjectManager::AddGameObject(EGameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void EGameObjectManager::OnStart()
{
	for (std::list<EGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		(*it)->OnStart();
}

void EGameObjectManager::Update()
{
	/*for (unsigned i = 0; i < m_GameObjects.size(); ++i)
		m_GameObjects[i]->Update();*/

	for (std::list<EGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		(*it)->Update();
}

void EGameObjectManager::FreeGameObjects()
{
	/*for (unsigned i = 0; i < m_GameObjects.size(); ++i)
	{
		m_GameObjects[i]->Destroy();
		delete m_GameObjects[i];
	}*/

	for (std::list<EGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	m_GameObjects.clear();
}

EGameObject* EGameObjectManager::GetGameObject(std::string name)
{
	/*for (unsigned i = 0; i < m_GameObjects.size(); ++i)
		if (m_GameObjects[i]->GetName().compare(name) == 0)
			return m_GameObjects[i];*/

	for (std::list<EGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		if ((*it)->m_Name.compare(name) == 0)
			return (*it);

	return 0;
}
