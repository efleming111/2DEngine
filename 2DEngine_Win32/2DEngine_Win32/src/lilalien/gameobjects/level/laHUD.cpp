//
//  lil Alien
//  laHUD.cpp
//  Eric Fleming
//  6/1/2018
//

#include "laHUD.h"

void laHUD::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);
}

void laHUD::OnStart()
{
	mPlayer = (laPlayer*)lilGameObjectManager->GetGameObjectByName("Player");
	mCamera = (laCamera*)lilGameObjectManager->GetGameObjectByName("Camera");

	mTransform = mCamera->mTransform;

	std::string numbers[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	for(int i = 0; i < 10; ++i)
		mNumberRenderables[i] = lilGLRenderer->GetRenderable(numbers[i].c_str());

	std::string names[] = { "100000s", "10000s", "1000s" , "100s" , "10s" , "1s" };
	for(int i = 0; i < 6; ++i)
		mCoinAmount[i] = (lilSprite*)GetComponentByName(names[i].c_str());

	DisplayPlayerCoins();

	mHealthAmount = (lilSprite*)GetComponentByName("HealthAmount");
	mFullHealth = mHealthAmount->transform.scale.x;
	UpdateHealthAmount();
}

void laHUD::Update()
{
	mTransform = mCamera->mTransform;

	if (mLastCoinAmount != mPlayer->GetCoins())
		DisplayPlayerCoins();

	UpdateHealthAmount();

	lilGameObject::Update();
}

void laHUD::Destroy()
{
	lilGameObject::Destroy();

	mPlayer = 0;
	mCamera = 0;

	for(int i = 0; i < 10; ++i)
		mNumberRenderables[i] = 0;

	for(int i = 0; i < 6; ++i)
		mCoinAmount[i] = 0;

	mHealthAmount = 0;
}

void laHUD::DisplayPlayerCoins()
{
	mLastCoinAmount = mPlayer->GetCoins();
	if (mLastCoinAmount < 999999)
	{
		int place = 100000;
		int coins = mLastCoinAmount;
		for (int i = 0; i < 6; ++i)
		{
			int placeNumber = coins / place;
			coins %= place;

			mCoinAmount[i]->renderable = mNumberRenderables[placeNumber];

			place /= 10;
		}
	}
}

void laHUD::UpdateHealthAmount()
{
	mHealthAmount->transform.scale.x = mPlayer->GetHealth() * mFullHealth;
	mHealthAmount->renderable->GetShader()->SetUniform("RGBalance", mPlayer->GetHealth());
}
