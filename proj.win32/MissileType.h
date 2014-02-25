#pragma once
#include "texturedgameobjecttype.h"
#include "cocos2d.h"

class MissileType :
	public TexturedGameObjectType
{
public:
	~MissileType(void);
	
	// returns HERO, UNIT, MISSILE, BOSS
	virtual const char* getObjectType(void) const
	{
		return STR_MISSILE;
	}

	CREATE_WITH_DICT(MissileType);
};

