//
//  lil Knight
//  lilHUD.cpp
//  Eric Fleming
//  6/1/2018
//

#include "lilHUD.h"

void HUD::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);
}

void HUD::OnStart()
{
	m_Player = (Player*)lilGameObjectManager->GetGameObjectByName("Player");
	m_Camera = (Camera*)lilGameObjectManager->GetGameObjectByName("Camera");

	m_Transform = m_Camera->m_Transform;

	std::string numbers[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	for(int i = 0; i < 10; ++i)
		m_NumberRenderables[i] = lilGLRenderer->GetRenderable(numbers[i].c_str());

	std::string names[] = { "100000s", "10000s", "1000s" , "100s" , "10s" , "1s" };
	for(int i = 0; i < 6; ++i)
		m_CoinAmount[i] = (ESprite*)GetComponentByName(names[i].c_str());

	DisplayPlayerCoins();

	m_HealthAmount = (ESprite*)GetComponentByName("healthamount");
	m_FullHealth = m_HealthAmount->transform.scale.x;
	UpdateHealthAmount();

	m_MagicAmount = (ESprite*)GetComponentByName("magicamount");
	m_FullMagic = m_MagicAmount->transform.scale.x;
	UpdateMagicAmount();
}

void HUD::Update()
{
	m_Transform = m_Camera->m_Transform;

	if (m_LastCoinAmount != m_Player->GetCoins())
		DisplayPlayerCoins();

	UpdateHealthAmount();
	UpdateMagicAmount();

	EGameObject::Update();
}

void HUD::Destroy()
{
	EGameObject::Destroy();

	m_Player = 0;
	m_Camera = 0;

	for(int i = 0; i < 10; ++i)
		m_NumberRenderables[i] = 0;

	for(int i = 0; i < 6; ++i)
		m_CoinAmount[i] = 0;

	m_HealthAmount = 0;
	m_MagicAmount = 0;
}

void HUD::DisplayPlayerCoins()
{
	m_LastCoinAmount = m_Player->GetCoins();
	if (m_LastCoinAmount < 999999)
	{
		int place = 100000;
		int coins = m_LastCoinAmount;
		for (int i = 0; i < 6; ++i)
		{
			int placeNumber = coins / place;
			coins %= place;

			m_CoinAmount[i]->renderable = m_NumberRenderables[placeNumber];

			place /= 10;
		}
	}
}

void HUD::UpdateHealthAmount()
{
	m_HealthAmount->transform.scale.x = m_Player->GetHealth() * m_FullHealth;
	m_HealthAmount->renderable->GetShader()->SetUniform("RGBalance", m_Player->GetHealth());
}

void HUD::UpdateMagicAmount()
{
	m_MagicAmount->transform.scale.x = m_Player->GetMagic() * m_FullMagic;
	m_MagicAmount->renderable->GetShader()->SetUniform("RGBalance", m_Player->GetMagic());
}
