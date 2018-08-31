//
//  2DEngine
//  and_Input.cpp
//  Eric Fleming
//  4/2/2018
//

#include "and_Input.h"
#include "../renderer/lilGLWindow.h"
#include "../renderer/lilGLRenderer.h"
#include "../core/lilCore.h"
#include "../utilities/lilFileIO.h"

lilInputAbstractionLayer::lilInputAbstractionLayer()
{
	mTouch = 0;
}


bool lilInputAbstractionLayer::Initialize()
{
	mScreenWidth = lilGLWindow->Width();
	mScreenHeight = lilGLWindow->Height();

	mTouch = new lilTouch();
	if (!mTouch->Initialize())
	{
		SDL_Log("ERROR: Touch Failed To Initialize %s %d", __FILE__, __LINE__);
		return false;
	}

	return LoadData();
}

void lilInputAbstractionLayer::Update()
{
	// Update input
	mTouch->Update();

	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
		case SDL_FINGERDOWN:
			mTouch->SetFingerTouch(mEvent.tfinger.fingerId, true, mEvent.tfinger.x, mEvent.tfinger.y);
			break;

		case SDL_FINGERMOTION:
			mTouch->SetFingerTouch(mEvent.tfinger.fingerId, true, mEvent.tfinger.x, mEvent.tfinger.y);
			break;

		case SDL_FINGERUP:
			mTouch->SetFingerTouch(mEvent.tfinger.fingerId, false, mEvent.tfinger.x, mEvent.tfinger.y);
			break;
		}
	}
}

void lilInputAbstractionLayer::Shutdown()
{
	delete mTouch;
	mTouch = 0;
}

bool lilInputAbstractionLayer::LoadData()
{
	char* xmlFile = lilFileIO::ReadFile("data/Input.xml", "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
		return false;

	for (TiXmlElement* input = rootElement->FirstChildElement(); input; input = input->NextSiblingElement())
	{
		std::string inputName;
		lilButton button;
		double temp;

		TiXmlElement* name = input->FirstChildElement("name");
		inputName = name->Attribute("name");

		TiXmlElement* touchButton = input->FirstChildElement("touchbutton");
		touchButton->Attribute("x", &temp);
		button.x = (float)temp;
		touchButton->Attribute("y", &temp);
		button.y = (float)temp;
		touchButton->Attribute("width", &temp);
		button.width = (float)temp;
		touchButton->Attribute("height", &temp);
		button.height = (float)temp;

		mUserInput[inputName].button = button;
	}

	return true;
}
