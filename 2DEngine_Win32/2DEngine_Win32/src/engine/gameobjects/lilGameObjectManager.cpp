//
//  2DEngine
//  lilGameObjectManager.h
//  Eric Fleming
//  5/24/2018
//

#include "lilGameObjectManager.h"
#include <SDL.h>

laGameObjectManager* laGameObjectManager::sInstance = 0;

laGameObjectManager* laGameObjectManager::Instance()
{
	if (!sInstance)
		sInstance = new laGameObjectManager();

	return sInstance;
}

void laGameObjectManager::AddGameObject(lilGameObject* gameObject)
{
	mGameObjects.push_back(gameObject);
}

void laGameObjectManager::OnStart()
{
	for (std::list<lilGameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
		(*it)->OnStart();
}

void laGameObjectManager::Update()
{
	for (std::list<lilGameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
		(*it)->Update();
}

void laGameObjectManager::FreeGameObjects()
{
	for (std::list<lilGameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	mGameObjects.clear();
}

lilGameObject* laGameObjectManager::GetGameObjectByType(std::string type)
{
	for (std::list<lilGameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
		if ((*it)->mType.compare(type) == 0)
			return (*it);

	return 0;
}

lilGameObject* laGameObjectManager::GetGameObjectByName(std::string name)
{
	for (std::list<lilGameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
		if ((*it)->mName.compare(name) == 0)
			return (*it);

	return 0;
}
