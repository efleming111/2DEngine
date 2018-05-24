//
//  lil Knight
//  lilLevel.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <vector>

class lilLevel
{
public:
	lilLevel() {}
	~lilLevel() {}

	void Create(const char* filename);
	void Update();
	void Destroy();

	void LoadLevel(const char* filename);

public:
	int m_CurrentLevelIndex;

private:
	lilLevel(const lilLevel& level) {}
	void operator=(const lilLevel& level) {}
};

