//
//  2DEngine
//  EGameObjectManager.h
//  Eric Fleming
//  5/24/2018
//

#include "EGameObjectManager.h"
#include "../components/ELogic.h"

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
	for (unsigned i = 0; i < m_GameObjects.size(); ++i)
	{
		ELogic* logicComponet = (ELogic*)m_GameObjects[i]->GetComponent("logic");
		if (logicComponet)
			logicComponet->OnStart();
	}
}

void EGameObjectManager::Update()
{
	for (unsigned i = 0; i < m_GameObjects.size(); ++i)
		m_GameObjects[i]->Update();
}

void EGameObjectManager::FreeGameObjects()
{
	for (unsigned i = 0; i < m_GameObjects.size(); ++i)
	{
		m_GameObjects[i]->Destroy();
		delete m_GameObjects[i];
	}

	m_GameObjects.clear();
}

EGameObject* EGameObjectManager::GetGameObject(std::string name)
{
	for (unsigned i = 0; i < m_GameObjects.size(); ++i)
		if (m_GameObjects[i]->GetName().compare(name) == 0)
			return m_GameObjects[i];

	return 0;
}
