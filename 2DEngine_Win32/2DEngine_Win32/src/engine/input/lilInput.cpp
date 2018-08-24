//
//  2DEngine
//  lilInput.cpp
//  Eric Fleming
//  4/2/2018
//

#include <sstream>

#include "lilInput.h"
#include "../renderer/lilGLWindow.h"
#include "../renderer/lilGLRenderer.h"
#include "../core/lilCore.h"
#include "../utilities/lilFileIO.h"

laInput* laInput::sInstance = 0;

laInput* laInput::Instance()
{
	if (!sInstance)
		sInstance = new laInput();

	return sInstance;
}

bool laInput::Initialize()
{
	mScreenWidth = lilGLWindow->Width();
	mScreenHeight = lilGLWindow->Height();

	mInputAbstractionLayer = new lilInputAbstractionLayer();
	mInputAbstractionLayer->Initialize(mScreenWidth, mScreenHeight);

	return LoadData();
}

void laInput::Update()
{
	mInputAbstractionLayer->Update();
}

void laInput::Shutdown()
{
	mInputAbstractionLayer->Shutdown();
}

bool laInput::LoadData()
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
		UserDefinedInput* userInput = new UserDefinedInput();

		TiXmlElement* name = input->FirstChildElement("name");
		userInput->name = name->Attribute("name");

		TiXmlElement* keyboard = input->FirstChildElement("keyboard");
		for (TiXmlAttribute* key = keyboard->FirstAttribute(); key; key = key->Next())
			userInput->keyboardCodes.push_back((KeyCode)key->IntValue());

		TiXmlElement* mouse = input->FirstChildElement("mouse");
		userInput->mouseButtonCode = (MouseButton)mouse->FirstAttribute()->IntValue();

		TiXmlElement* joystick = input->FirstChildElement("joystickbutton");
		userInput->joystickButtonCode = (JoystickButton)joystick->FirstAttribute()->IntValue();
	}

	return true;
}
