//
//  2DEngine
//  ELogicComponent.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <string>

#include "EComponent.h"

class ELogicComponent : public EComponent
{
public:
	ELogicComponent(EGameObject* gameObject) { m_GameObject = gameObject; }
	~ELogicComponent() {}

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

	void SetLogicFunction(void(*logicFunction)(EGameObject* gameobject)) { UpdateLogic = logicFunction; }
	std::string& GetFunctionName() { return m_FunctionName; }

protected:
	std::string m_FunctionName;
	void(*UpdateLogic)(EGameObject* gameObject);

private:
	ELogicComponent(const ELogicComponent& component) {}
	void operator=(const ELogicComponent& component) {}
};