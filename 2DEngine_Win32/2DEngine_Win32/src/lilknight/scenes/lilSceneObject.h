//
//  lil Knight
//  lilSceneObject.h
//  Eric Fleming
//  5/30/2018
//

#pragma once

#include <string>

#include "../../engine/gameobjects/EGameObject.h"

class SceneObject : public EGameObject
{
public:
	SceneObject() {}
	~SceneObject() {}
	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	std::string& GetNextScene() { return m_NextScene; }
	bool ChangeScene() { return m_ChangeScene; }

private:
	std::string m_NextScene;
	bool m_ChangeScene;

private:
	SceneObject(const SceneObject& scene) {}
	void operator=(const SceneObject& scene) {}
};


