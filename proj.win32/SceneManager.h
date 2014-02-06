#pragma once
#include "cocos2d.h"
#include "PreloadedScene.h"
#include "LoadingScene.h"
#include "myLib.h"
#include "GameEventsMacros.h"
//#include "IHasAnyKeyToContinue.h"

USING_NS_CC;

class SceneManager : public CCNode
{
private:
	PreloadedScene *m_nextScene;
	queue<PreloadedScene*>* m_scenes;
	CCDirector *m_director;
	//static SceneManager *m_sceneManager;

	float m_trasitionDuration;

	void progressListenerCallback(int, int, int);
	void loadingSceneContinueCallback();
	void loadingCompleteCallback(CCObject* obj);

public:
	~SceneManager(void);
	//static SceneManager* sharedSceneManager(void);
	bool loadScene(PreloadedScene *preloadedScene);
	bool loadScene(PreloadedScene *preloadedScene, bool withLoadingScene);
	void setTrasitionDuration(float);

	CC_SHARED_CREATE_FUNC(SceneManager);
};

