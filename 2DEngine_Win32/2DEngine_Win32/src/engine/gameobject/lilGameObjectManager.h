//
//  2DEngine
//  lilGameObjectManager.h
//  Eric Fleming
//  5/24/2018
//

#pragma once

#include <list>
#include <string>

#include "lilGameObject.h"

#define lilGameObjectManager laGameObjectManager::Instance()

class laGameObjectManager
{
public:
	// Returns only instance of game object manager
	static laGameObjectManager* Instance();

	// Adds game object to manager
	// @ filename - name of game object
	void AddGameObject(lilGameObject* gameObject);

	// Call once just before update runs
	void OnStart();

	// Calls update on all game objects
	void Update();

	// Frees all loaded shaders
	void FreeGameObjects();

	// Gets pointer to first game object of type, type
	// @ type - type of game object
	lilGameObject* GetGameObjectByType(std::string type);

	// Gets pointer to first game object of name, name
	// @ name - name of game object
	lilGameObject* GetGameObjectByName(std::string name);

private:
	static laGameObjectManager* s_Instance;

	std::list<lilGameObject*> m_GameObjects;

private:
	// Only instance of  game manager object, no copying
	laGameObjectManager() {}
	~laGameObjectManager() {}
	laGameObjectManager(const laGameObjectManager& shaderManager) {}
	void operator=(const laGameObjectManager& shaderManager) {}
};

