//
//  lil Knight
//  lilScene.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <string>

#include "lilSceneObject.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

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
	float m_PixelsPerGameUnit;

private:
	// No copying
	lilScene(const lilScene& scene) {}
	void operator=(const lilScene& scene) {}

	// Creates all resources and game objects for scene
	void LoadRenderableResources(TiXmlElement* resources);
	void GameObjectFactory(TiXmlElement* rootElement);
};

