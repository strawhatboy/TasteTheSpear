#pragma once
#include "cocos2d.h"

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

#define CREATE_WITH_DICT(__TYPE__)\
public:\
	__TYPE__(CCDictionary* dict);\
	static __TYPE__* createWithDict(CCDictionary* dict)\
	{\
		__TYPE__* pRet = new __TYPE__(dict);\
		if (pRet)\
			return pRet;\
		else\
		{\
			CC_SAFE_DELETE(pRet);\
		}\
		return NULL;\
	}

class GameObjectType
{
	CC_SYNTHESIZE_READONLY(const char*, m_pszName, Name);
	CC_SYNTHESIZE_READONLY(const char*, m_pszDescription, Description);
	CC_SYNTHESIZE_READONLY(const char*, m_pszTypeID, TypeID);
	CC_SYNTHESIZE_READONLY(const char*, m_pszTexture, Texture);
	//CC_SYNTHESIZE_READONLY(CCArray*, m_Animations, Animations);

public:
	~GameObjectType(void);
	GameObjectType(CCDictionary* dict);
	//CREATE_WITH_DICT(GameObjectType);

	// returns HERO, UNIT, MISSILE, BOSS, should never return STR_GAMEOBJECT
	virtual const char* getObjectType(void) const = 0;
};

