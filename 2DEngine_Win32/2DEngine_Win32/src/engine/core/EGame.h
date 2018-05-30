//
//  2DEngine
//  EGame.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

// Pure abstract class, overridden with the game
class EGame
{
public:
	EGame() {}
	virtual ~EGame() {}

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual void CleanUp() = 0;

private:
	EGame(const EGame& game) {}
	void operator=(const EGame& game) {}
};