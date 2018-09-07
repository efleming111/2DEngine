//
//  lil Alien
//  laCamera.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include "../../../engine/gameobjects/lilGameObjectManager.h"
#include "../../../engine/gameobjects/lilTransform.h"
#include "../characters/laPlayer.h"

class laPlayer;

class laCamera : public lilGameObject
{
public:
	laCamera() {}
	~laCamera() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

private:
	laPlayer* mPlayer;

private:
	laCamera(const laCamera& camera) {}
	void operator=(const laCamera& camera) {}
};