#pragma once
#include "cocos2d.h"
#include "myLib.h"
//#include "IHasAnyKeyToContinue.h"
#include "LoadingLayer.h"
//#include "IProgressBroadcaster.h"
#include "ProgressEntity.h"
#include "IHasProgress.h"
#include "GameEventsMacros.h"

USING_NS_CC;


// 0.5s delay of the loading scene to avoid the next scene load too fast.
#define SWITCH_DELAY 0.5f

class LoadingScene :
	public CCScene
	,public IHasProgress
	//, public IHasAnyKeyToContinue
	//, public IProgressBroadcaster
{
private:
	LoadingLayer* m_loadingLayer;
	void loadingLayerLoadingCompleteCallback(CCObject* obj);
	void delayTimerCallback(float elapsedTime);
	bool bIsDelayed;
	bool bIsLoadingComplete;

public:
	~LoadingScene(void);
	void SetLoadingLayer(LoadingLayer*);
	void Refresh(void);
	
	virtual void setProgress(ProgressEntity* progress);

	CC_SHARED_CREATE_FUNC(LoadingScene);
};

