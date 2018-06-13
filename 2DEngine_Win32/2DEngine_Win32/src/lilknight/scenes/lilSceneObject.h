//
//  lil Knight
//  lilSceneObject.h
//  Eric Fleming
//  5/30/2018
//

#pragma once

#include <map>
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

	void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
	void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

	std::string& GetNextScene() { return m_NextScene; }
	bool ChangeScene() { return m_ChangeScene; }

	void GetPlayerStart(float* x, float *y);

private:
	bool m_IsStarterScene;

	std::map<std::string, std::string> m_LoadOptions;
	std::string m_NextScene;
	bool m_ChangeScene;

	float m_PlayerStartX;
	float m_PlayerStartY;

private:
	SceneObject(const SceneObject& scene) {}
	void operator=(const SceneObject& scene) {}
};


