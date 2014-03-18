#pragma once

#include "cocos2d.h"
#include "PreloadedScene.h"
#include "LoadingScene.h"
#include "HeroSelectLayer.h"

USING_NS_CC;

class HeroSelectScene :
	public PreloadedScene
{
public:
	HeroSelectScene(void);
	~HeroSelectScene(void);

	virtual bool init(void);

	virtual bool loadResources(void);
	virtual bool drawContents(void);

	static HeroSelectScene* create()
	{
		auto p = new HeroSelectScene();
		if (p && p->init())
		{
			p->autorelease();
			return p;
		}
		else
		{
			CC_SAFE_DELETE(p);
			return NULL;
		}
	}
};

