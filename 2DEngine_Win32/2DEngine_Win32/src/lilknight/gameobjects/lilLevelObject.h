//
//  lil Knight
//  lilLevelLogic.h
//  Eric Fleming
//  5/21/2018
//

#pragma once

#include "../../engine/components/ERigidbody.h"

// TODO: For testing only
#include <SDL.h>

class LevelObject : public EGameObject
{
public:
	LevelObject() {}
	~LevelObject() {}
	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
	void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

private:
	LevelObject(const LevelObject& levelObject) {}
	void operator=(const LevelObject& levelObject) {}
};

void BlockBeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
void BlockEndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

