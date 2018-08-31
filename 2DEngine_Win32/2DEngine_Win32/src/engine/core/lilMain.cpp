//
//  2DEngine
//  lilMain.cpp
//  Eric Fleming
//  4/2/2018
//

#include "lilCore.h"


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

