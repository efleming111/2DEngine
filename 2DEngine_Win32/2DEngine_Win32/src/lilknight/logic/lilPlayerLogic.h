//
//  lil Knight
//  lilPlayerLogic.h
//  Eric Fleming
//  5/21/2018
//

#include "../../engine/gameobjects/EGameObject.h"
#include "../../engine/input/EInput.h"
#include "../../engine/components/ERigidbody.h"
#include "../../engine/components/ELogic.h"
#include "../../engine/components/EAnimator.h"

// TODO: For testing only
#include <SDL.h>

#pragma once

class PlayerLogic : public ELogicObject
{
public:
	PlayerLogic() {}
	~PlayerLogic() {}

	void Create();
	void OnStart();
	void Update();
	void Destroy();

protected:
	ERigidbody* m_Rigidbody;
	EAnimator* m_Animator;

	bool m_IsFacingRight;

private:
	PlayerLogic(const PlayerLogic& logic) {}
	void operator=(const PlayerLogic& logic) {}
};

void PlayerBeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
void PlayerEndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

