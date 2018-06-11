//
//  lil Knight
//  lilAndroidControls.h
//  Eric Fleming
//  6/11/2018
//

#pragma once

#include <list>
#include <string>

#include "../../engine/components/ESprite.h"
#include "lilCamera.h"

// TODO: For testing only
#include <SDL.h>

struct Button
{
	std::string name;

	float x;
	float y;

	float left;
	float right;
	float bottom;
	float top;
};

class ButtonControls : public EGameObject
{
public:
	ButtonControls() {}
	~ButtonControls() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();



private:
	Camera* m_Camera;
	std::list<Button*> m_Buttons;

private:
	ButtonControls(const ButtonControls& levelObject) {}
	void operator=(const ButtonControls& levelObject) {}
};



