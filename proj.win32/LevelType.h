#pragma once
#include "TexturedGameObjectType.h"

class LevelType : 
	public TexturedGameObjectType
{

public:
	~LevelType(void);

	// returns HERO, UNIT, MISSILE, LEVEL, DISTRICT
	virtual const char* getObjectType(void) const
	{
		return STR_LEVEL;
	}

	CREATE_WITH_DICT(LevelType);
};

