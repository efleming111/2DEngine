//
//  2DEngine
//  ESpriteComponent.h
//  Eric Fleming
//  5/20/2018
//

#pragma once

#include "EComponent.h"
#include "../gameobjects/ETransform.h"

class ESpriteComponent : public EComponent
{
public:
	ESpriteComponent(EGameObject* gameObject) { m_GameObject = gameObject; }
	~ESpriteComponent() {}

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

public:
	ETransform m_Transform;
	float m_XRel;
	float m_YRel;

	unsigned meshIndex;
	unsigned shaderIndex;
	unsigned textureID;

	bool isRendered;

private:
	ESpriteComponent(const ESpriteComponent& component) {}
	void operator=(const ESpriteComponent& component) {}
};

