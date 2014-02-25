#pragma once

#include "cocos2d.h"
#include "DistrictSelectLayer.h"

USING_NS_CC;

class DistrictSelectScene :
	public CCScene
{
public:
	virtual bool init();
	DistrictSelectScene(void);
	~DistrictSelectScene(void);

	CREATE_FUNC(DistrictSelectScene);
};

