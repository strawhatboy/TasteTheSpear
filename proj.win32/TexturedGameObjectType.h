#pragma once

#include "GameObjectType.h"

class TexturedGameObjectType :
	public GameObjectType
{
	CC_SYNTHESIZE_READONLY(string, m_pszTexture, Texture);

public:
	TexturedGameObjectType(CCDictionary* dict);
	~TexturedGameObjectType(void);

	// returns HERO, UNIT, MISSILE, BOSS, should never return STR_GAMEOBJECT
	virtual const char* getObjectType(void) const = 0;

	virtual bool loadArmature(
		CCObject* target = NULL,
		SEL_SCHEDULE selector = NULL) const;
};

