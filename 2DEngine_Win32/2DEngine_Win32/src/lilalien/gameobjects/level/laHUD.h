//
//  lil Alien
//  laHUD.h
//  Eric Fleming
//  6/1/2018
//

#pragma once

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

	lilSprite* mCoinAmount[2];
	lilSprite* mKeys[4];
	lilSprite* mTimer[3];
	lilSprite* mScore[7];

private:
	laHUD(const laHUD& hud) {}
	void operator=(const laHUD& hud) {}

	void SetDisplay(int value, lilSprite** sprites, int numberOfPlaces);
	void SetKeys();
};