#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mylib.h"
#include "GameObjectTypesLoader.h"
#include "ScrollLayer.h"
#include "GameDirector.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DistrictSelectLayer :
	public CCLayer
{
private:
	void districtSelected(CCObject* obj);

public:
	DistrictSelectLayer(void);
	~DistrictSelectLayer(void);

	virtual bool init();

	CREATE_FUNC(DistrictSelectLayer);
};

