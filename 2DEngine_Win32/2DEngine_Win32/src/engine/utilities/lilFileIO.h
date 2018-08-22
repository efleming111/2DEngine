//
//  2DEngine
//  lilFileIO.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

class lilFileIO
{
public:
	// Reads data from file
	// Returns pointer to data(client deletes pointer memory)
	// @ filename - name of file to read
	// @ mode - type of data
	static char* ReadFile(const char* filename, const char* mode);

	// Writes data to file
	// Returns true if write was successful
	// @ filename - name of file to write to
	// @ mode - type of data
	// @ data - data to be wrote to file
	static bool WriteFile(const char* filename, const char* mode, char* data);
};

