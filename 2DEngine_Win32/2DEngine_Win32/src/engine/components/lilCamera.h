//
//  2DEngine
//  lilCamera.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "lilComponent.h"

class lilCamera : public lilComponent
{
public:
	lilCamera(lilGameObject* gameObject) : lilComponent(gameObject) {}
	~lilCamera() {}

	// Creates a camera
	// @ element - data for setting up the camera
	void Create(TiXmlElement* element);

	// Updates the camera
	void Update();

	// Does nothing
	void Destroy();

	// Sets the position of the camera
	// @ x - x position
	// @ y - y position
	void SetPosition(float x, float y);

	// Moves the camera by the givven amount
	// @ xAmount - amount to move in the x axis
	// @ yAmount - amount to move in the y axis
	void Move(float xAmount, float yAmount);

	// Returns the view matrix
	glm::mat4& GetViewMatrix() { return mView; }

	// Returns the projection matrix
	glm::mat4& GetProjectionMatrix() { return mProjection; }

	// Returns the x position of the camera
	float X() { return mGameObject->mTransform.position.x; }

	// Returns the y position of the camera
	float Y() { return mGameObject->mTransform.position.y; }

protected:
	glm::mat4 mView;
	glm::mat4 mProjection;

private:
	// No copying
	lilCamera(const lilCamera& component) {}
	void operator=(const lilCamera& component) {}
};