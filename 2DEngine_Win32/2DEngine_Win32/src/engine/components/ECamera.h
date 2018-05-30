//
//  2DEngine
//  ECamera.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "EComponent.h"

class ECamera : public EComponent
{
public:
	ECamera(EGameObject* gameObject) : EComponent(gameObject) {}
	~ECamera() {}

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
	glm::mat4& GetViewMatrix() { return m_View; }

	// Returns the projection matrix
	glm::mat4& GetProjectionMatrix() { return m_Projection; }

	// Returns the x position of the camera
	float X() { return m_GameObject->m_Transform.position.x; }

	// Returns the y position of the camera
	float Y() { return m_GameObject->m_Transform.position.y; }

protected:
	glm::mat4 m_View;
	glm::mat4 m_Projection;

private:
	// No copying
	ECamera(const ECamera& component) {}
	void operator=(const ECamera& component) {}
};