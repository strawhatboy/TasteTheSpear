#pragma once

#include "cocos-ext.h"
#include "TexturedGameObjectType.h"
#include "GameObject_Runtime.h"

USING_NS_CC_EXT;

class TexturedGameObject_Runtime
	: public GameObject_Runtime
{
	CC_SYNTHESIZE_READONLY(CCArmature*, m_Armature, Armature);
	CC_SYNTHESIZE_READONLY(CCSprite*, m_Sprite, Sprite);

	CC_SYNTHESIZE_READONLY(TexturedGameObjectType*, m_TexturedObjectType, TexturedObjectType);

public:
	TexturedGameObject_Runtime(void);
	~TexturedGameObject_Runtime(void);
	
	virtual bool initWithGameObjectType(GameObjectType* type);
	virtual void playAnimation(const char* animationName,
		int durationTo = -1, int durationTween = -1, int loop = -1, int tweenEasing = 10000);

	virtual void playAnimation(int index,
		int durationTo = -1, int durationTween = -1, int loop = -1, int tweenEasing = 10000);

	// get the armature or sprite depend on its texture type.
	CCNodeRGBA* getTextureNode(void);

	RUNTIME_OBJ_CREATE(TexturedGameObject_Runtime, TexturedGameObjectType);
};

