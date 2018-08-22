//
//  2DEngine
//  lilAnimation.h
//  Eric Fleming
//  5/9/2018
//

#pragma once

#include <list>

#include "../../../../thirdpartysrc/tinyxml/tinyxml.h"
#include "../lilSprite.h"

class lilAnimation
{
public:
	lilAnimation() {}
	~lilAnimation() {}

	// Creates an animation
	// @ element - tag which stores all animation data
	// @ gameobject - game object this animation belongs to
	void Create(TiXmlElement* element, lilGameObject* gameObject);

	// Updates the animation
	void Update();

	// Does nothing, the renderer frees all sprites
	void Destroy();

	// Starts or restarts the animation at the first fram
	void StartAnimation();

	// Stops the animation sequence form playing
	// Renders the animation invisible
	void StopAnimation();

	// Flips the animation along its y axis
	void FlipAnimationX();

	// Sets the time between frames
	void SetIntervalTime(float interval) { m_TimeBetweenFrames = interval; }

	// Return true if animation has finished playing
	bool IsAnimationFinished() { return m_IsFinished; }

	void IsRendered(bool isRendered);
	
	std::list<lilSprite*>::iterator m_CurrentFrame;
private:
	std::list<lilSprite*> m_Frames;

	//std::list<ESprite*>::iterator m_CurrentFrame;

	float m_TimeBetweenFrames;
	float m_AccumlativeTime;

	bool m_IsLooping;
	bool m_IsFinished;

	bool m_IsRendered;

private:
	// No copying
	lilAnimation(const lilAnimation& animation) {}
	void operator=(const lilAnimation& animation) {}
};