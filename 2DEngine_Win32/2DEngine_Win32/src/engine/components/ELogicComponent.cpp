//
//  2DEngine
//  ELogicComponent.cpp
//  Eric Fleming
//  5/18/2018
//

#include "ELogicComponent.h"

void ELogicComponent::Create(TiXmlElement* element)
{
	m_Name = element->Attribute("name");
	m_FunctionName = element->Attribute("function");
}

void ELogicComponent::Update()
{
	UpdateLogic(m_GameObject);
}

void ELogicComponent::Destroy()
{
	UpdateLogic = 0;
}
