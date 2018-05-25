//
//  lil Knight
//  lilCamera.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include "../../engine/gameobjects/EGameObjectManager.h"
#include "../../engine/gameobjects/ETransform.h"
#include "lilPlayer.h"

class Camera : public EGameObject
{
public:
	Camera() {}
	~Camera() {}

	void Create(const char* filename, float pixelsPerGameUnit);
	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

private:
	Player * m_Player;

private:
	Camera(const Camera& logic) {}
	void operator=(const Camera& logic) {}
};