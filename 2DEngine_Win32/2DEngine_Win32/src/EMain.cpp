//
//  2DEngine
//  EMain.cpp
//  Eric Fleming
//  4/2/2018
//

#include "engine\core\ECore.h"


int main(int argc, char* argv[])
{
	lilEngine->HandleCommandArgs(argc, argv);

	if (lilEngine->Initialize())
	{
		lilEngine->Run();
		lilEngine->ShutDown();
	}

	return 0;
}

