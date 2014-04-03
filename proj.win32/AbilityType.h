#pragma once
#include "texturedgameobjecttype.h"

#define STR_ABILITY_DATA "data"

class AbilityType :
	public TexturedGameObjectType
{
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_Data, Data);

public:
	~AbilityType(void);

	float getAbilityData(const char* key);

	// returns HERO, UNIT, MISSILE, LEVEL, DISTRICT
	virtual string getObjectType(void) const
	{
		return STR_ABILITY;
	}

	CREATE_WITH_DICT(AbilityType);
};

