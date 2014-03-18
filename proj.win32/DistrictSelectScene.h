#pragma once

#include "cocos2d.h"
#include "DistrictSelectLayer.h"
#include "PreloadedScene.h"

USING_NS_CC;

class DistrictSelectScene :
	public PreloadedScene
{
public:
	virtual bool init();
	DistrictSelectScene(void);
	~DistrictSelectScene(void);

	virtual bool loadResources(void);
	virtual bool drawContents(void);

	CREATE_FUNC(DistrictSelectScene);
};

