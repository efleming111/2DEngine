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

	// Gets pointer to first game object of type, type
	// @ type - type of game object
	EGameObject* GetGameObjectByType(std::string type);

	// Gets pointer to first game object of name, name
	// @ name - name of game object
	EGameObject* GetGameObjectByName(std::string name);

private:
	static EGameObjectManager* s_Instance;

	std::list<EGameObject*> m_GameObjects;

private:
	// Only instance of  game manager object, no copying
	EGameObjectManager() {}
	~EGameObjectManager() {}
	EGameObjectManager(const EGameObjectManager& shaderManager) {}
	void operator=(const EGameObjectManager& shaderManager) {}
};

