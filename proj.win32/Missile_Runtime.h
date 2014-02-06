#pragma once
#include "missileType.h"
#include "gameobject_runtime.h"
#include "myLib.h"

class Missile_Runtime :
	public GameObject_Runtime
{
public:
	Missile_Runtime(void);
	~Missile_Runtime(void);

	RUNTIME_OBJ_CREATE(Missile_Runtime, MissileType);
};

