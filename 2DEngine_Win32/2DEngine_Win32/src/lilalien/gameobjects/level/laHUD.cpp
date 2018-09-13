//
//  lil Alien
//  laHUD.cpp
//  Eric Fleming
//  6/1/2018
//

#include <vector>

#include "../../../engine/renderer/lilGLWindow.h"

#include "laHUD.h"

void laHUD::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);

	float xGameUnits = lilGLWindow->Width() / pixelsPerGameUnit;
	float yGameUnits = lilGLWindow->Height() / pixelsPerGameUnit;

	for (std::list<lilComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if ((*it)->GetType().compare("Sprite") == 0)
		{
			((lilSprite*)(*it))->xRelative = (((lilSprite*)(*it))->xRelative * xGameUnits) - (xGameUnits *.5f);
			((lilSprite*)(*it))->yRelative = (((lilSprite*)(*it))->yRelative * yGameUnits) - (yGameUnits *.5f);
		}
	}
}

void laHUD::OnStart()
{
	mPlayer = (laPlayer*)lilGameObjectManager->GetGameObjectByName("Player");
	mCamera = (laCamera*)lilGameObjectManager->GetGameObjectByName("Camera");

	mTransform = mCamera->mTransform;

	std::string numbers[] = { "HUD0", "HUD1", "HUD2", "HUD3", "HUD4", "HUD5", "HUD6", "HUD7", "HUD8", "HUD9" };
	for(int i = 0; i < 10; ++i)
		mNumberRenderables[i] = lilGLRenderer->GetRenderable(numbers[i].c_str());

	std::string coinNames[] = { "CoinTens", "CoinOnes" };
	for(int i = 0; i < 2; ++i)
		mCoinAmount[i] = (lilSprite*)GetComponentByName(coinNames[i].c_str());

	std::string keyNames[] = { "KeyYellow", "KeyGreen", "KeyRed", "KeyBlue" };
	for (int i = 0; i < 4; ++i)
		mKeys[i] = (lilSprite*)GetComponentByName(keyNames[i].c_str());

	std::string timerNames[] = { "TimerHundreds", "TimerTens", "TimerOnes" };
	for (int i = 0; i < 3; ++i)
		mTimer[i] = (lilSprite*)GetComponentByName(timerNames[i].c_str());

	std::string scoreNames[] = { "ScoreMillions", "ScoreHundredThousands", "ScoreTenThousands", "ScoreThousands", "ScoreHundreds", "ScoreTens", "ScoreOnes" };
	for (int i = 0; i < 7; ++i)
		mScore[i] = (lilSprite*)GetComponentByName(scoreNames[i].c_str());

	SetDisplay(mPlayer->GetCoins(), mCoinAmount, 2);
	SetDisplay(mPlayer->GetScore(), mScore, 7);

}

void laHUD::Update()
{
	mTransform = mCamera->mTransform;

	/*if (mLastCoinAmount != mPlayer->GetCoins())
		DisplayPlayerCoins();*/

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
}

void laHUD::SetDisplay(int value, lilSprite** sprites, int numberOfPlaces)
{
	int place = 1;
	for (int i = 1; i < numberOfPlaces; ++i)
		place *= 10;

	for (int i = 0; i < numberOfPlaces; ++i)
	{
		int placeNumber = value / place;
		value %= place;

		sprites[i]->renderable = mNumberRenderables[placeNumber];

		place /= 10;
	}
}

void laHUD::SetKeys()
{
	for (int i = 0; i < 4; ++i)
	{
		mKeys[i]->isRendered = mPlayer->GetKeys()[i];
	}
}
