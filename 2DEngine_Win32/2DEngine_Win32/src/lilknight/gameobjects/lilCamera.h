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

class Player;

class Camera : public EGameObject
{
public:
	Camera() {}
	~Camera() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

private:
	Player* m_Player;

private:
	Camera(const Camera& camera) {}
	void operator=(const Camera& camera) {}
};