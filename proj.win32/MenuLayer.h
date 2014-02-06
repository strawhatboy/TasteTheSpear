#pragma once
#include "cocos2d.h"
#include "GameObjectTypesLoader.h"
#include "CCLuaEngine.h"

#define MENU_CONFIG_FILE_NAME "menu_config.plist"
#define MENU_ITEMS_FILE_NAME "menu_items.plist"
#define STR_MENU_START "start"
#define STR_MENU_SETTINGS "settings"
#define STR_MENU_HELP "help"
#define STR_MENU_ABOUT "about"
#define TAG_MENU_START 10
#define TAG_MENU_SETTINGS 11
#define TAG_MENU_HELP 12
#define TAG_MENU_ABOUT 13

USING_NS_CC;
class MenuLayer :
	public CCLayer
{
public:
	virtual bool init(void);
	virtual bool init(bool bIsPausingMenu);
	MenuLayer(void);
	~MenuLayer(void);
	CREATE_FUNC(MenuLayer);
	static MenuLayer* create(bool bIsPausingMenu)
	{
		MenuLayer* pRet = new MenuLayer();
		if (pRet && pRet->init(bIsPausingMenu))
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			CC_SAFE_DELETE(pRet);
			return NULL;
		}
	}

private:
	CCMenu* getRandomMenuItems(int startCount,
		int settingsCount,
		int helpCount,
		int aboutCount);
	CCMenu* getRandomMenuItems(int startCount,
		int settingsCount,
		int helpCount,
		int aboutCount,
		bool isPausingMenu);
	
	CCMenuItem* getRandomMenuItem(const char* pszType,
		int nCount);

	CCMenuItem* getRandomMenuItem(const char* pszType,
		int nCount, bool bIsSelected);

	void menuCallback(CCObject* sender);
};

