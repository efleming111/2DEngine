//
//  2DEngine
//  lilInput.cpp
//  Eric Fleming
//  4/2/2018
//

#include <sstream>

#include "lilInput.h"

laInput* laInput::sInstance = 0;

laInput* laInput::Instance()
{
	if (!sInstance)
		sInstance = new laInput();

	return sInstance;
}

bool laInput::Initialize()
{
	mInputAbstractionLayer = new lilInputAbstractionLayer();
	mInputAbstractionLayer->Initialize();

	return true;
}

void laInput::Update()
{
	mInputAbstractionLayer->Update();
}

void laInput::Shutdown()
{
	mInputAbstractionLayer->Shutdown();
}


