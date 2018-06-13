//
//  lil Knight
//  lilLevelLogic.h
//  Eric Fleming
//  5/21/2018
//

#include "lilButtonControls.h"
#include "../../engine/input/EInput.h"

#include "../../engine/renderer/EGLWindow.h"
#include "../../engine/gameobjects/EGameObjectManager.h"

void ButtonControls::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);

	rootElement->Attribute("numberofbuttons", &m_NumberOfButtons);
	m_Buttons = new Button[m_NumberOfButtons];

	TiXmlElement* buttonPositions = rootElement->FirstChildElement("buttonpositions");
	int index = 0;
	for (TiXmlElement* position = buttonPositions->FirstChildElement(); position; position = position->NextSiblingElement())
	{
		m_Buttons[index].name = position->Attribute("name");

		double x, y;
		position->Attribute("x", &x);
		position->Attribute("y", &y);

		m_Buttons[index].xRel = (((float)x * (float)lilGLWindow->Width()) - ((float)lilGLWindow->Width() * .5f)) / m_PixelsPerGameUnit;
		m_Buttons[index].yRel = (((float)y * (float)lilGLWindow->Height()) - ((float)lilGLWindow->Height() * .5f)) / m_PixelsPerGameUnit;

		m_Buttons[index].x = (float)x;
		m_Buttons[index].y = (float)y;

		m_Buttons[index].buttonState.isPressed = false;
		m_Buttons[index].buttonState.isDown = false;

		++index;
	}
}

void ButtonControls::OnStart()
{
	m_Camera = (Camera*)lilGameObjectManager->GetGameObjectByName("Camera");
	m_Transform = m_Camera->m_Transform;

	for (int i = 0; i < m_NumberOfButtons; ++i)
	{
		ESprite* buttonSprite = (ESprite*)GetComponentByName(m_Buttons[i].name.c_str());
		buttonSprite->xRelative = m_Buttons[i].xRel;
		buttonSprite->yRelative = m_Buttons[i].yRel;

		m_Buttons[i].left = m_Buttons[i].x * lilGLWindow->Width() - (buttonSprite->transform.scale.x * .5f * m_PixelsPerGameUnit);
		m_Buttons[i].right = m_Buttons[i].x * lilGLWindow->Width() + (buttonSprite->transform.scale.x * .5f * m_PixelsPerGameUnit);
		m_Buttons[i].bottom = m_Buttons[i].y * lilGLWindow->Height() - (buttonSprite->transform.scale.y * .5f * m_PixelsPerGameUnit);
		m_Buttons[i].top = m_Buttons[i].y * lilGLWindow->Height() + (buttonSprite->transform.scale.y * .5f * m_PixelsPerGameUnit);
	}
}

void ButtonControls::Update()
{
	m_Transform = m_Camera->m_Transform;

	SetButtons();

	EGameObject::Update();
}

void ButtonControls::Destroy()
{
	delete[] m_Buttons;
	m_Buttons = 0;

	EGameObject::Destroy();
}

void ButtonControls::SetButtons()
{
#ifdef _WIN32
	for (int i = 0; i < m_NumberOfButtons; ++i)
		m_Buttons[i].buttonState.isPressed = false;

	if (lilMouse->GetButton(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < m_NumberOfButtons; ++i)
		{
			float mouseX = lilMouse->X();
			float mouseY = lilMouse->Y();
			if (lilMouse->X() > m_Buttons[i].left && lilMouse->X() < m_Buttons[i].right &&
				lilMouse->Y() > m_Buttons[i].bottom && lilMouse->Y() < m_Buttons[i].top)
			{
				if (!m_Buttons[i].buttonState.isDown)
				{
					m_Buttons[i].buttonState.isPressed = true;
					m_Buttons[i].buttonState.isDown = true;
				}
			}

			else
			{
				m_Buttons[i].buttonState.isPressed = false;
				m_Buttons[i].buttonState.isDown = false;
			}
		}
	}

	else
	{
		for (int i = 0; i < m_NumberOfButtons; ++i)
		{
			m_Buttons[i].buttonState.isPressed = false;
			m_Buttons[i].buttonState.isDown = false;
		}
	}
#endif

#ifdef __ANDROID__
	Finger* fingers = lilTouch->GetTouches();
	for (int i = 0; i < m_NumberOfButtons; ++i)
	{
		for (int j = 0; j < MAX_FINGER_TOUCHES; ++j)
		{
			float touchX = fingers[j].x;
			float touchY = lilGLWindow->Height() - fingers[j].y;
			if (touchX > m_Buttons[i].left && touchX < m_Buttons[i].right &&
				touchY > m_Buttons[i].bottom && touchY < m_Buttons[i].top &&
				fingers[j].isTouching)
			{
				if(m_Buttons[i].buttonState.isDown)
					m_Buttons[i].buttonState.isPressed = false;
				else
					m_Buttons[i].buttonState.isPressed = true;

				m_Buttons[i].buttonState.isDown = true;
				break;
			}

			else
			{
				m_Buttons[i].buttonState.isPressed = false;
				m_Buttons[i].buttonState.isDown = false;
			}
		}
	}
#endif
}

bool ButtonControls::GetButton(int index)
{
	if (index >= 0 && index < m_NumberOfButtons)
		return m_Buttons[index].buttonState.isDown;

	return false;
}

bool ButtonControls::GetButtonDown(int index)
{
	if (index >= 0 && index < m_NumberOfButtons)
		return m_Buttons[index].buttonState.isPressed;

	return false;
}

