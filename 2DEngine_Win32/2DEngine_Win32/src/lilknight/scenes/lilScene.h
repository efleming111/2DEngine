//
//  lil Knight
//  lilScene.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <string>
#include "lilSceneObject.h"

class lilScene
{
public:
	lilScene() {}
	~lilScene() {}

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
	SceneObject* m_SceneObject;

private:
	// No copying
	lilScene(const lilScene& scene) {}
	void operator=(const lilScene& scene) {}

	// Creates all game objects for scene
	void GameObjectFactory(const char* filename);
};

