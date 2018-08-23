//
//  2DEngine
//  EKeyboard.cpp
//  Eric Fleming
//  4/2/2018
//

#include "EKeyboard.h"

bool EKeyboard::Initialize()
{
	for (int i = 0; i < NUMBER_OF_KEYS; ++i)
	{
		m_Keys[i].pressed = false;
		m_Keys[i].down = false;
	}

	return true;
}

void EKeyboard::Update()
{
	for (int i = 0; i < NUMBER_OF_KEYS; ++i)
		m_Keys[i].pressed = false;
}

void EKeyboard::SetKey(KeyCode keyCode, bool isPressed)
{
	if (isPressed)
	{
		if (!m_Keys[keyCode].down)
		{
			m_Keys[keyCode].pressed = true;
			m_Keys[keyCode].down = true;
		}
	}

	else
	{
		m_Keys[keyCode].pressed = false;
		m_Keys[keyCode].down = false;
	}
}


bool EKeyboard::GetKey(KeyCode keyCode) const
{
	if (keyCode >= 0 && keyCode < NUMBER_OF_KEYS)
	{
		return m_Keys[keyCode].down;
	}

	return false;
}

bool EKeyboard::GetKeyDown(KeyCode keyCode) const
{
	if (keyCode >= 0 && keyCode < NUMBER_OF_KEYS)
	{
		return m_Keys[keyCode].pressed;
	}

	return false;
}

