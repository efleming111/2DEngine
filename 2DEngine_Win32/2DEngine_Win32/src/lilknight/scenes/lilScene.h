//
//  lil Knight
//  lilLevel.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <string>

class lilScene
{
public:
	lilScene() {}
	~lilScene() {}

	// Creates scene from filename passed
	// @ filename - file name of scene data
	void Create(const char* filename);
	void Update();
	void Destroy();

public:
	// Variables used to change scenes
	bool sceneChangeRequest;
	std::string nextSceneToLoad;

private:
	// No copying
	lilScene(const lilScene& level) {}
	void operator=(const lilScene& level) {}

	// Creates all game objects for scene
	void GameObjectFactory(const char* filename);
};

