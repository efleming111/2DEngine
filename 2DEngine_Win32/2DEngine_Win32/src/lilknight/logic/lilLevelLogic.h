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

void BlockBeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
void BlockEndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

