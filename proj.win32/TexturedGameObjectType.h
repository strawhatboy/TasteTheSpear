#pragma once

#include "GameObjectType.h"

class TexturedGameObjectType :
	public GameObjectType
{
	CC_SYNTHESIZE_READONLY(string, m_pszTexture, Texture);

	// is armature or just a frame in some texture.
	CC_SYNTHESIZE_READONLY(bool, m_bIsArmature, IsArmature);

public:
	TexturedGameObjectType(CCDictionary* dict);
	~TexturedGameObjectType(void);

	// returns HERO, UNIT, MISSILE, BOSS, should never return STR_GAMEOBJECT
	virtual string getObjectType(void) const = 0;

	virtual bool loadTexture(
		CCObject* target = NULL,
		SEL_SCHEDULE selector = NULL) const;
};

