#include "LoadingScene.h"

CC_SHARED_CREATE_IMPL(LoadingScene);

LoadingScene::LoadingScene(void)
{
	INIT_POINTER(this->m_loadingLayer);
	//INIT_POINTER(this->m_progress);
	//this->Refresh();
	//this->m_progress = new ProgressEntity();
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(
		LoadingScene::loadingLayerLoadingCompleteCallback), EVENT_LOADING_LAYER_LOADING_COMPLETE, NULL);
}


LoadingScene::~LoadingScene(void)
{
	//CC_SAFE_DELETE(this->m_progress);
}


void LoadingScene::loadingLayerLoadingCompleteCallback(CCObject* obj)
{
	if (this->bIsDelayed)
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_LOADING_COMPLETE);
	this->bIsLoadingComplete = true;
	this->schedule(schedule_selector(LoadingScene::delayTimerCallback), SWITCH_DELAY);
}

void LoadingScene::delayTimerCallback(float elapsedTime)
{
	this->unschedule(schedule_selector(LoadingScene::delayTimerCallback));
	auto sharedLoadingScene = LoadingScene::sharedInstance();
	if (sharedLoadingScene->bIsLoadingComplete)
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_LOADING_COMPLETE);
	sharedLoadingScene->bIsDelayed = true;
}
//void LoadingScene::setCurrentValue(int currentValue)
//{
//	//IHasProgress::setCurrentValue(currentValue);
//	//if (currentValue == this->m_maxValue)
//	{
//		//this->OnFinish();
//		//if (IHasAnyKeyToContinue::IsAnyKeyToContinueEnabled())
//		{
//
//		}
//	}
//
//
//}

void LoadingScene::SetLoadingLayer(LoadingLayer* loadingLayer)
{
	this->m_loadingLayer = loadingLayer;

	// loadingLayer is now in GC, will not delete it in destructor.
	this->addChild(this->m_loadingLayer);
}

//void LoadingScene::increaseCurrentValue(int alpha)
//{
//	//this->setCurrentValue(this->m_currentValue + alpha);
//	auto progress = this->m_progress;
//	progress->setCurrentValue(progress->getCurrentValue() + 1);
//}


void LoadingScene::setProgress(ProgressEntity* progress)
{
	if (this->m_loadingLayer)
		this->m_loadingLayer->setProgress(progress);
}
void LoadingScene::Refresh(void)
{
	this->bIsDelayed = false;
	this->bIsLoadingComplete = false;
}