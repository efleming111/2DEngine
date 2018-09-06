//
//  lil Knight
//  lilScene.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <string>

#include "../gameobjects/laLevelController.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

class laLevelManager
{
public:
	laLevelManager() {}
	~laLevelManager() {}

	// Creates scene from filename passed
	// @ filename - file name of scene data
	void Create(const char* filename);

	// Updates the scene
	void Update();

	// Cleans up scene
	void Destroy();

public:
	bool loadNewScene;
	std::string nextSceneFilename;

private:
	laLevelController* mLevelController;
	float mPixelsPerGameUnit;

private:
	// No copying
	laLevelManager(const laLevelManager& scene) {}
	void operator=(const laLevelManager& scene) {}

	// Creates all resources and game objects for scene
	void LoadRenderableResources(TiXmlElement* resources);
	void GameObjectFactory(TiXmlElement* rootElement);
};

