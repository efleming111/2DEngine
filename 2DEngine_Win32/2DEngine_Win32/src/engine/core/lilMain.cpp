//
//  2DEngine
//  lilMain.cpp
//  Eric Fleming
//  4/2/2018
//

#include "lilCore.h"

// Work thru separating windows and android code into separate header files
   Core GLWindow Input
// Rename files with lil prefix to show done file
// Complete engine then revies game files

// Load input file
// Call functions into platform specific class that in turn calls into device class
// ie lilInput -> getButton("Left") -> calls in to keyboard mouse joystick or touch button

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

