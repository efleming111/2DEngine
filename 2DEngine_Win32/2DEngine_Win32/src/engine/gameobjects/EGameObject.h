//
//  2DEngine
//  EGameObject.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <string>
#include <list>

#include "ETransform.h"
#include "../components/EComponent.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

class EComponent;
class ERigidbody;

// Game object class that every gam object should derive from
class EGameObject
{
public:
	EGameObject() {}
	virtual ~EGameObject() {}

	// Creates game object
	// THIS FUNCTION MUST BE CALLED BY DERIVED CLASS
	virtual void Create(const char* filename, float pixelsPerGameUnit) = 0;

	// Creates game object
	// THIS FUNCTION MUST BE CALLED BY DERIVED CLASS
	virtual void Create(TiXmlElement* rootElement, float pixelsPerGameUnit) = 0;

	// Called just before the game loop runs
	// Override in derived class
	virtual void OnStart() = 0;

	// Updates game object
	// THIS FUNCTION MUST BE CALLED AT THE END OF THE UPDATE OF THE DERIVED CLASS
	virtual void Update() = 0;

	// Destroys game object
	// THIS FUNCTION MUST ONLY BE CALLED BY THE DERIVED CLASS
	virtual void Destroy() = 0;

	// Handles collision with other objects
	// IF GAME OBJECT CONTAINS A RIGIDBODY THIS FUNCTION MUST CONTAIN LOGIC FOR PHYSIC IN DERIVED CLASS
	virtual void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody) {}

	// Handles collision with other objects
	// IF GAME OBJECT CONTAINS A RIGIDBODY THIS FUNCTION MUST CONTAIN LOGIC FOR PHYSIC IN DERIVED CLASS
	virtual void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody) {}

	// Returns requested conponent of game object
	// Returns 0 if component does not exist
	EComponent* GetComponent(const char* type);

public:
	std::string m_Name;
	ETransform m_Transform;
	float m_PixelsPerGameUnit;

protected:
	std::list<EComponent*> m_Components;

private:
	void CreateComponents(TiXmlElement* components);
};