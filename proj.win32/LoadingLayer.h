#pragma once
#include "cocos2d.h"
#include "ProgressEntity.h"
#include "IHasProgress.h"

#define BG_LOADING_CONFIG_FILE_NAME "bg_loading_config.plist"
#define EVENT_LOADING_LAYER_LOADING_COMPLETE "EVENT_LOADING_LAYER_LOADING_COMPLETE"

USING_NS_CC;


class LoadingLayer :
	public CCLayer 
	, public IHasProgress
{
public:
	LoadingLayer(void);
	~LoadingLayer(void);
};

