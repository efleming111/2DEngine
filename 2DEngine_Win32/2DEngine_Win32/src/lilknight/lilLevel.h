//
//  lil Knight
//  lilLevel.cpp
//  Eric Fleming
//  5/17/2018
//

#pragma once

class lilLevel
{
public:
	lilLevel() {}
	~lilLevel() {}

	void Create(const char* filename) {}
	void Destroy() {}
	void Update() {}

public:
	int m_CurrentLevelIndex;

private:

private:

private:
	lilLevel(const lilLevel& level) {}
	void operator=(const lilLevel& level) {}
};

