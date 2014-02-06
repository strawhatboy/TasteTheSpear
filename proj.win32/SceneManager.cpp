#include "SceneManager.h"

CC_SHARED_CREATE_IMPL(SceneManager);

SceneManager::SceneManager(void)
{
	this->m_director = CCDirector::sharedDirector();
	this->m_scenes = new queue<PreloadedScene*>();
	this->m_trasitionDuration = .2f;
	INIT_POINTER(this->m_nextScene);

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, 
		callfuncO_selector(SceneManager::loadingCompleteCallback),
		EVENT_LOADING_COMPLETE, NULL);
}

SceneManager::~SceneManager(void)
{
}


bool SceneManager::loadScene(PreloadedScene *preloadedScene)
{
	return loadScene(preloadedScene, true);
}


bool SceneManager::loadScene(PreloadedScene *preloadedScene, bool withLoadingScene)
{
	bool bRet = false;

	do
	{
		//preloadedScene->retain();

		if (preloadedScene == NULL)
		{
			CCLog("Failed to push a preloaded scene because it's null.");
			return false;
		}
		
		this->addChild(preloadedScene);

		if (this->m_nextScene != NULL)
		{
			CCLog("There is already a scene loading now, this scene will be added to queue.");
			this->m_scenes->push(preloadedScene);
		}
		else
		{
			this->m_nextScene = preloadedScene;
			auto loadingScene = LoadingScene::sharedInstance();
			loadingScene->Refresh();
			CCTransitionFade* fade = CCTransitionFade::create(this->m_trasitionDuration, loadingScene);

			// use pushScene here to delete the previous scene;
			this->m_director->pushScene(fade);
			CCLog("LoadingScene loaded.");
			//preloadedScene->addListener(BROADCAST_PROGRESS(SceneManager::progressListenerCallback));

			//if (loadingScene->IsAnyKeyToContinueEnabled())
			//{
			//	loadingScene->AddContinueListener(CONTINUE_SELECTOR(SceneManager::loadingSceneContinueCallback));
			//}
			//else
			//{
			//	loadingScene->AddFinishListener(FINISH_SELECTOR(SceneManager::loadingSceneContinueCallback));
			//}

			bRet = bRet || preloadedScene->loadResources();
			CC_BREAK_IF(bRet);
		}
	}while (0);

	return bRet;
}

void SceneManager::loadingCompleteCallback(CCObject* obj)
{
	//auto sharedThis = SceneManager::sharedInstance();
	if (this->m_nextScene)
	{
		CCTransitionFade* fade = CCTransitionFade::create(this->m_trasitionDuration, this->m_nextScene);

		//use replaceScene here to avoid deleting LoadingScene because it's a singleton
		CCDirector::sharedDirector()->replaceScene(fade);

		this->m_nextScene->drawContents();
		this->removeChild(this->m_nextScene);
		this->m_nextScene = NULL;

		//scene switch success, dump texture info
		CCLog("Cached Texture:");
		CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
		CCLog("Cached Texture: (after remove unused texture)");
		CCTextureCache::sharedTextureCache()->removeUnusedTextures();
		CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
	}

	if (!this->m_scenes->empty())
	{
		this->loadScene(this->m_scenes->front());
		this->m_scenes->pop();
	}
}

void SceneManager::progressListenerCallback(int minValue, int maxValue, int currentValue)
{
	auto loadingScene = LoadingScene::sharedInstance();
	//loadingScene->setMinValue(minValue);
	//loadingScene->setMaxValue(maxValue);
	//loadingScene->setCurrentValue(currentValue);
}

void SceneManager::loadingSceneContinueCallback()
{
	auto sharedThis = SceneManager::sharedInstance();
	// m_nextScene != NULL means the loading scene is running.
	if (sharedThis->m_nextScene)
	{
		CCTransitionFade* fade = CCTransitionFade::create(sharedThis->m_trasitionDuration, sharedThis->m_nextScene);
		sharedThis->m_director->replaceScene(fade);
		sharedThis->m_nextScene = NULL;
	}

	if (!sharedThis->m_scenes->empty())
	{
		sharedThis->loadScene(sharedThis->m_scenes->front());
		sharedThis->m_scenes->pop();
	}
}


void SceneManager::setTrasitionDuration(float duration)
{
	this->m_trasitionDuration = duration;
}