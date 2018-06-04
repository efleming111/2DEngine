//
//  lil Knight
//  lilHUD.h
//  Eric Fleming
//  6/1/2018
//

#pragma once

#include <list>

#include "../../engine/gameobjects/EGameObject.h"
#include "../../engine/renderer/EGLRenderer.h"
#include "lilPlayer.h"
#include "lilCamera.h"

class HUD : public EGameObject
{
public:
	HUD() {}
	~HUD() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

protected:
	Player* m_Player;
	Camera* m_Camera;

	ERenderable* m_NumberRenderables[10];
	ESprite* m_CoinAmount[6];
	int m_LastCoinAmount;

	ESprite* m_HealthAmount;
	float m_FullHealth;
	ESprite* m_MagicAmount;
	float m_FullMagic;

private:
	HUD(const HUD& hud) {}
	void operator=(const HUD& hud) {}

	void DisplayPlayerCoins();
	void UpdateHealthAmount();
	void UpdateMagicAmount();
};