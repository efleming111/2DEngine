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
	void SetIntervalTime(float interval) { mTimeBetweenFrames = interval; }

	// Return true if animation has finished playing
	bool IsAnimationFinished() { return mIsFinished; }

	void IsRendered(bool isRendered);
	
	std::list<lilSprite*>::iterator mCurrentFrame;
private:
	std::list<lilSprite*> mFrames;

	//std::list<ESprite*>::iterator mCurrentFrame;

	float mTimeBetweenFrames;
	float mAccumlativeTime;

	bool mIsLooping;
	bool mIsFinished;

	bool mIsRendered;

private:
	// No copying
	lilAnimation(const lilAnimation& animation) {}
	void operator=(const lilAnimation& animation) {}
};