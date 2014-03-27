#pragma once
#include "cocos2d.h"
#include "myLib.h"
USING_NS_CC;

#define STR_GAMEOBJECT_NAME "name"
#define STR_GAMEOBJECT_DESCRIPTION "description"
#define STR_GAMEOBJECT_TYPEID "typeid"
#define STR_GAMEOBJECT_TEXTURE "texture"
//#define STR_GAMEOBJECT_ANIMATION "animations"

#define STR_GAMEOBJECT "OBJECT"
#define STR_FIGHTINGUNIT "UNIT"
#define STR_HERO "HERO"
#define STR_BOSS "BOSS"
#define STR_MISSILE "MISSILE"
#define STR_DISTRICT "DISTRICT"
#define STR_LEVEL "LEVEL"
#define STR_TEXTURE "TEXTURE"
#define STR_STRINGRESOURCE "STRING"
#define STR_ABILITY "ABILITY"

class GameObjectType :
	public CCNode
{
	CC_SYNTHESIZE_READONLY(string, m_pszName, Name);
	CC_SYNTHESIZE_READONLY(string, m_pszDescription, Description);
	CC_SYNTHESIZE_READONLY(string, m_pszTypeID, TypeID);
	//CC_SYNTHESIZE_READONLY(CCArray*, m_Animations, Animations);

public:
	~GameObjectType(void);
	GameObjectType(CCDictionary* dict);
	//CREATE_WITH_DICT(GameObjectType);

	// returns HERO, UNIT, MISSILE, BOSS, should never return STR_GAMEOBJECT
	virtual const char* getObjectType(void) const = 0;
};

