#pragma once
#include "missileType.h"
#include "TexturedGameObject_Runtime.h"
#include "myLib.h"

class Missile_Runtime :
	public TexturedGameObject_Runtime
{
public:
	Missile_Runtime(void);
	~Missile_Runtime(void);

	RUNTIME_OBJ_CREATE(Missile_Runtime, MissileType);
};

