//
//  2DEngine
//  lilGameObjectManager.h
//  Eric Fleming
//  5/24/2018
//

#include "lilGameObjectManager.h"
#include <SDL.h>

laGameObjectManager* laGameObjectManager::s_Instance = 0;

laGameObjectManager* laGameObjectManager::Instance()
{
	if (!s_Instance)
		s_Instance = new laGameObjectManager();

	return s_Instance;
}

void laGameObjectManager::AddGameObject(lilGameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void laGameObjectManager::OnStart()
{
	for (std::list<lilGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		(*it)->OnStart();
}

void laGameObjectManager::Update()
{
	for (std::list<lilGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		(*it)->Update();
}

void laGameObjectManager::FreeGameObjects()
{
	for (std::list<lilGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	m_GameObjects.clear();
}

lilGameObject* laGameObjectManager::GetGameObjectByType(std::string type)
{
	for (std::list<lilGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		if ((*it)->m_Type.compare(type) == 0)
			return (*it);

	return 0;
}

lilGameObject* laGameObjectManager::GetGameObjectByName(std::string name)
{
	for (std::list<lilGameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		if ((*it)->m_Name.compare(name) == 0)
			return (*it);

	return 0;
}
