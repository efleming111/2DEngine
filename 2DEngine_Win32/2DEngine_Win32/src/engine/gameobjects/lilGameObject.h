//
//  2DEngine
//  lilGameObject.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <string>
#include <list>

#include "lilTransform.h"
#include "../components/lilComponent.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

class lilComponent;
class lilRigidbody;

// Game object class that every game object should derive from
class lilGameObject
{
public:
	lilGameObject() {}
	virtual ~lilGameObject() {}

	// Creates game object
	// THIS FUNCTION MUST BE CALLED FIRST BY DERIVED CLASS
	virtual void Create(TiXmlElement* rootElement, float pixelsPerGameUnit) = 0;

	// Called just before the game loop runs
	// Override in derived class
	virtual void OnStart() = 0;

	// Updates game object
	// THIS FUNCTION MUST BE CALLED AT THE END OF THE UPDATE OF THE DERIVED CLASS
	virtual void Update() = 0;

	// Destroys game object
	// THIS FUNCTION MUST BE CALLED BY THE DERIVED CLASS
	virtual void Destroy() = 0;

	// Handles collision with other objects
	// IF GAME OBJECT CONTAINS A RIGIDBODY THIS FUNCTION MUST CONTAIN LOGIC FOR PHYSIC IN DERIVED CLASS
	virtual void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody) {}

	// Handles collision with other objects
	// IF GAME OBJECT CONTAINS A RIGIDBODY THIS FUNCTION MUST CONTAIN LOGIC FOR PHYSIC IN DERIVED CLASS
	virtual void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody) {}

	// Returns requested conponent of game object
	// Returns 0 if component does not exist
	lilComponent* GetComponentByType(const char* type);

	// Returns requested conponent of game object
	// Returns 0 if component does not exist
	lilComponent* GetComponentByName(const char* name);

public:
	std::string mType;
	std::string mName;
	lilTransform mTransform;
	float mPixelsPerGameUnit;

protected:
	std::list<lilComponent*> mComponents;

private:
	void CreateComponents(TiXmlElement* components);
};

