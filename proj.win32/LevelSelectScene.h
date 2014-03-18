#pragma once


#include "cocos2d.h"
#include "LevelSelectLayer.h"
#include "PreloadedScene.h"

USING_NS_CC;

class LevelSelectScene :
	public PreloadedScene
{
public:
	virtual bool init(const char* districtTypeID = "");
	LevelSelectScene(void);
	~LevelSelectScene(void);

	
	virtual bool loadResources(void);
	virtual bool drawContents(void);

	
	static LevelSelectScene* create(const char* districtTypeID = "")
	{
		auto p = new LevelSelectScene();
		if (p && p->init(districtTypeID))
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

