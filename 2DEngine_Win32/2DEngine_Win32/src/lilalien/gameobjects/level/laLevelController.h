//
//  lil Alien
//  laLevelController.h
//  Eric Fleming
//  5/30/2018
//

#pragma once

#include <map>
#include <string>

#include "../../../engine/gameobjects/lilGameObject.h"

class laLevelController : public lilGameObject
{
public:
	laLevelController() {}
	~laLevelController() {}
	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);
	void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);

	std::string& GetNextScene() { return mNextScene; }
	bool ChangeScene() { return mChangeScene; }

	void GetPlayerStart(float* x, float *y);

private:
	bool mIsDefaultLevel;

	std::map<std::string, std::string> mLoadOptions;
	std::string mNextScene;
	bool mChangeScene;

	float mPlayerStartX;
	float mPlayerStartY;

private:
	laLevelController(const laLevelController& scene) {}
	void operator=(const laLevelController& scene) {}
};


