#pragma once
#include "cocos2d.h"
#include "PreloadedScene.h"
#include "LoadingScene.h"
#include "MenuLayer.h"
#include "TutsauLayer.h"

USING_NS_CC;

class MenuScene :
	public PreloadedScene
{
public:
	virtual bool init();
	MenuScene(void);
	~MenuScene(void);
	CC_CREATE_FUNC(MenuScene);
	virtual bool loadResources();
	virtual bool drawContents();
	virtual void onEnter();

private:
	/*CCMenuItem* GetStartMenuItem();
	CCMenuItem* GetSettingsMenuItem();
	CCMenuItem* GetHelpMenuItem();
	CCMenuItem* GetAboutMenuItem();*/
	void menuNewGameCallback(CCObject* sender);
	void resourceLoadedCallback(CCObject*);

	void testTuTsau(float elapsedTime);
};

