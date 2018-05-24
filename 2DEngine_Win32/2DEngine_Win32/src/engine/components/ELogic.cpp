//
//  2DEngine
//  ELogic.cpp
//  Eric Fleming
//  5/18/2018
//

#include "ELogic.h"

void ELogic::Create(TiXmlElement* element)
{
	m_Type = element->Attribute("type");
}

void ELogic::Update()
{
	m_Logic->Update();
}

void ELogic::Destroy()
{
	m_Logic->Destroy();
	delete m_Logic;
	m_Logic = 0;
}

void ELogic::SetLogicObject(ELogicObject* logic)
{
	m_Logic = logic;
	if (m_Logic)
	{
		std::vector<EComponent*> components;
		unsigned i = 0;
		for (EComponent* component = m_GameObject->GetComponent(i); component; component = m_GameObject->GetComponent(i))
		{
			components.push_back(component);
			++i;
		}

		m_Logic->Setup(m_GameObject, components);
		m_Logic->Create();
	}
}

void ELogic::OnStart()
{
	m_Logic->OnStart();
}
