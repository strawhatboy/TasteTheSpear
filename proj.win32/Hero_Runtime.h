#pragma once
#include "HeroType.h"
#include "fightingunit_runtime.h"
#include "cocos2d.h"
#include "myLib.h"

class Hero_Runtime :
	public FightingUnit_Runtime
{
public:
	Hero_Runtime(void);
	~Hero_Runtime(void);

	RUNTIME_OBJ_CREATE(Hero_Runtime, HeroType);
};

