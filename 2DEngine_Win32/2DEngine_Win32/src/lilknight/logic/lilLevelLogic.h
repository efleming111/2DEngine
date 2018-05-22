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

void BlockBeginContact(ERigidbody* other)
{
	SDL_Log("Block Begin Contact, %s %d", __FILE__, __LINE__);
}

void BlockEndContact(ERigidbody* other)
{
	SDL_Log("Block End Contact, %s %d", __FILE__, __LINE__);
}

