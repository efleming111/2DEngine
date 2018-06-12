//
//  lil Knight
//  lilAndroidControls.h
//  Eric Fleming
//  6/11/2018
//

#pragma once

#include <string>

#include "../../engine/components/ESprite.h"
#include "lilCamera.h"

// TODO: For testing only
#include <SDL.h>

struct ButtonState
{
	bool isPressed;
	bool isDown;
};

struct Button
{
	std::string name;

	float xRel;
	float yRel;

	float x;
	float y;

	float left;
	float right;
	float bottom;
	float top;

	ButtonState buttonState;
};

class Camera;

class ButtonControls : public EGameObject
{
public:
	ButtonControls() {}
	~ButtonControls() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	// Is button down
	bool GetButton(int index);

	// Per frame button was pressed
	bool GetButtonDown(int index);

private:
	Camera* m_Camera;

	Button* m_Buttons;
	int m_NumberOfButtons;

private:
	ButtonControls(const ButtonControls& levelObject) {}
	void operator=(const ButtonControls& levelObject) {}

	void SetButtons();
};



