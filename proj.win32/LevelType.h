#pragma once
#include "TexturedGameObjectType.h"

#define STR_LEVEL_SCRIPT "script"

class LevelType : 
	public TexturedGameObjectType
{
	CC_SYNTHESIZE_READONLY(string, m_Script, Script);
public:
	~LevelType(void);

	// returns HERO, UNIT, MISSILE, LEVEL, DISTRICT
	virtual const char* getObjectType(void) const
	{
		return STR_LEVEL;
	}

	CREATE_WITH_DICT(LevelType);
};

