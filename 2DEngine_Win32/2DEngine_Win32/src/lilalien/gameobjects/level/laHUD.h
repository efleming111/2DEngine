//
//  lil Alien
//  laHUD.h
//  Eric Fleming
//  6/1/2018
//

#pragma once

#include <list>

#include "../../../engine/gameobjects/lilGameObject.h"
#include "../../../engine/renderer/lilGLRenderer.h"
#include "../characters/laPlayer.h"
#include "laCamera.h"

class laHUD : public lilGameObject
{
public:
	laHUD() {}
	~laHUD() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

protected:
	laPlayer* mPlayer;
	laCamera* mCamera;

	lilRenderable* mNumberRenderables[10];
	lilSprite* mCoinAmount[6];
	int mLastCoinAmount;

	lilSprite* mHealthAmount;
	float mFullHealth;

private:
	laHUD(const laHUD& hud) {}
	void operator=(const laHUD& hud) {}

	void DisplayPlayerCoins();
	void UpdateHealthAmount();
};