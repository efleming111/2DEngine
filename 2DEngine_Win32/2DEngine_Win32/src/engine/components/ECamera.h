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

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

	void SetPosition(float x, float y);
	void Move(float xAmount, float yAmount);

	glm::mat4& GetViewMatrix() { return m_View; }
	glm::mat4& GetProjectionMatrix() { return m_Projection; }

	float X() { return m_GameObject->m_Transform.position.x; }
	float Y() { return m_GameObject->m_Transform.position.y; }

protected:
	glm::mat4 m_View;
	glm::mat4 m_Projection;

private:
	ECamera(const ECamera& component) {}
	void operator=(const ECamera& component) {}
};