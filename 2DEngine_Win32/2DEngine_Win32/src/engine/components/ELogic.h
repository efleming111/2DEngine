//
//  2DEngine
//  ELogic.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <string>
#include <vector>

#include "EComponent.h"
 
class ELogicObject
{
public:
	ELogicObject() {}
	virtual ~ELogicObject() {}

	void Setup(EGameObject* gameObject, std::vector<EComponent*> components)
	{
		m_GameObject = gameObject;
		m_Compnonets = components;
	}

	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

protected:
	EGameObject* m_GameObject;
	std::vector<EComponent*> m_Compnonets;

private:
	ELogicObject(const ELogicObject& logic) {}
	void operator=(const ELogicObject& logic) {}
};

class ELogic : public EComponent
{
public:
	ELogic(EGameObject* gameObject) { m_GameObject = gameObject; }
	~ELogic() {}

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

	void SetLogicObject(ELogicObject* logic);

protected:
	ELogicObject * m_Logic;

private:
	ELogic(const ELogic& component) {}
	void operator=(const ELogic& component) {}
};