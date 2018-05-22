//
//  2DEngine
//  ESprite.h
//  Eric Fleming
//  5/20/2018
//

#pragma once

#include "EComponent.h"
#include "../gameobjects/ETransform.h"

class ESprite : public EComponent
{
public:
	ESprite(EGameObject* gameObject) { m_GameObject = gameObject; }
	~ESprite() {}

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
	ESprite(const ESprite& component) {}
	void operator=(const ESprite& component) {}
};

