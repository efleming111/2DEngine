//
//  2DEngine
//  EGameObjectManager.h
//  Eric Fleming
//  5/24/2018
//

#pragma once

#include <list>
#include <string>

#include "EGameObject.h"

#define lilGameObjectManager EGameObjectManager::Instance()

class EGameObjectManager
{
public:
	// Returns only instance of game object manager
	static EGameObjectManager* Instance();

	// Adds game object to manager
	// @ filename - name of game object
	void AddGameObject(EGameObject* gameObject);

	// Call once just before update runs
	void OnStart();

	// Calls update on all game objects
	void Update();

	// Frees all loaded shaders
	void FreeGameObjects();

	// Gets pointer to game object
	// @ name - name of game object
	EGameObject* GetGameObject(std::string name);

	unsigned Size() { return (unsigned)m_GameObjects.size(); }

private:
	static EGameObjectManager* s_Instance;

	std::list<EGameObject*> m_GameObjects;

private:
	EGameObjectManager() {}
	~EGameObjectManager() {}
	EGameObjectManager(const EGameObjectManager& shaderManager) {}
	void operator=(const EGameObjectManager& shaderManager) {}
};

