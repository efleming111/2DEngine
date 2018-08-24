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

laInput* laInput::s_Instance = 0;

laInput* laInput::Instance()
{
	if (!s_Instance)
		s_Instance = new laInput();

	return s_Instance;
}

bool laInput::Initialize()
{
	m_ScreenWidth = lilGLWindow->Width();
	m_ScreenHeight = lilGLWindow->Height();

	return LoadData();
}

void laInput::Update()
{
	// Call Update of the platform specific input class
}

void laInput::Shutdown()
{
	// Call Shutdown of the platform specific input class
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
