//
//  2DEngine
//  EMain.cpp
//  Eric Fleming
//  4/2/2018
//

#include "engine\core\ECore.h"
#include "lilknight\lilKnightGame.h"

int main(int argc, char* argv[])
{
	lilEngine->HandleCommandArgs(argc, argv);

	if (lilEngine->Initialize())
	{
		// ADD NEW GAME OBJECT HERE
		lilEngine->LoadGame(new lilKnightGame());
		lilEngine->Run();
		lilEngine->ShutDown();
	}

	return 0;
}

