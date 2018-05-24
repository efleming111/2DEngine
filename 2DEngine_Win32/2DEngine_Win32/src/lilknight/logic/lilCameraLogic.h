//
//  lil Knight
//  lilCameraLogic.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include "../../engine/components/ELogic.h"
#include "../../engine/gameobjects/EGameObjectManager.h"
#include "../../engine/gameobjects/ETransform.h"

class CameraLogic : public ELogicObject
{
public:
	CameraLogic() {}
	~CameraLogic() {}

	void Create();
	void OnStart();
	void Update();
	void Destroy();

protected:
	EGameObject* m_Player;

private:
	CameraLogic(const CameraLogic& logic) {}
	void operator=(const CameraLogic& logic) {}
};