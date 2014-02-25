#include "MenuLayer.h"

bool MenuLayer::init()
{
	return init(false);
}

bool MenuLayer::init(bool bIsPausingMenu)
{
	if (!CCLayer::init())
	{
		return false;
	}

	bool bRet = false;

	auto fileUtil = CCFileUtils::sharedFileUtils();
	//auto fullFilePath = fileUtil->fullPathForFilename(MENU_CONFIG_FILE_NAME);
	//auto plistDic = CCDictionary::createWithContentsOfFile(fullFilePath.c_str());
	auto plistDic = CCDictionary::createWithContentsOfFile(MENU_CONFIG_FILE_NAME);
	int startCount = plistDic->valueForKey(STR_MENU_START)->intValue();
	int settingsCount = plistDic->valueForKey(STR_MENU_SETTINGS)->intValue();
	int helpCount = plistDic->valueForKey(STR_MENU_HELP)->intValue();
	int aboutCount = plistDic->valueForKey(STR_MENU_ABOUT)->intValue();
	
	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	spriteFrameCache->addSpriteFramesWithFile(MENU_ITEMS_FILE_NAME);

	this->addChild(getRandomMenuItems(startCount,
		settingsCount,
		helpCount,
		aboutCount, bIsPausingMenu));
	bRet = true;
	return bRet;
}

MenuLayer::MenuLayer(void)
{
	CCLog("Menu layer created?!");
}


MenuLayer::~MenuLayer(void)
{
	CCLog("Menu layer deleted?!");
}

//#define GET_RANDOM_MENU_INDEX(__COUNT__) CCRANDOM_0_1() * __COUNT__ + 1;

CCMenu* MenuLayer::getRandomMenuItems(int startCount,
		int settingsCount,
		int helpCount,
		int aboutCount)
{
	return getRandomMenuItems(startCount,
		settingsCount,
		helpCount,
		aboutCount,
		false);
}
CCMenu* MenuLayer::getRandomMenuItems(int startCount,
		int settingsCount,
		int helpCount,
		int aboutCount,
		bool isPausingMenu)
{
	//int startIndex = GET_RANDOM_MENU_INDEX(startCount);
	//int settingstIndex = GET_RANDOM_MENU_INDEX(settingsCount);
	//int helpIndex = GET_RANDOM_MENU_INDEX(helpCount);
	//int aboutIndex = GET_RANDOM_MENU_INDEX(aboutCount);

	CCMenu* menu = CCMenu::create();
	if (!isPausingMenu)
		menu->addChild(getRandomMenuItem(STR_MENU_START, startCount));
	menu->addChild(getRandomMenuItem(STR_MENU_SETTINGS, settingsCount));
	menu->addChild(getRandomMenuItem(STR_MENU_HELP, helpCount));
	menu->addChild(getRandomMenuItem(STR_MENU_ABOUT, aboutCount));
	menu->alignItemsVerticallyWithPadding(10.0);
	return menu;
}

#define FORMAT_MENU_STRING "%s_%03d.png"
#define FORMAT_MENU_STRING_SELECTED "%s_%03d_selected.png"


CCMenuItem* MenuLayer::getRandomMenuItem(const char* pszType,
		int nCount)
{
	return getRandomMenuItem(pszType, nCount, false);
}

CCMenuItem* MenuLayer::getRandomMenuItem(const char* pszType,
		int nCount, bool bIsSelected)
{
	int index = CCRANDOM_0_1() * nCount + 1;

	CCString* menu_string_selected = CCString::createWithFormat(
			FORMAT_MENU_STRING_SELECTED, pszType, index);
	CCString* menu_string = CCString::createWithFormat(
			FORMAT_MENU_STRING, pszType, index);

	auto spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSprite* sprite_menu = CCSprite::createWithSpriteFrame(
		spriteFrameCache->spriteFrameByName(menu_string->getCString()));
	CCSprite* sprite_menu_selected = CCSprite::createWithSpriteFrame(
		spriteFrameCache->spriteFrameByName(menu_string_selected->getCString()));
	CCMenuItemSprite* menuItem = CCMenuItemSprite::create(sprite_menu, 
		sprite_menu_selected, NULL, this, menu_selector(MenuLayer::menuCallback));
	
	if (strcmp(pszType, STR_MENU_START) == 0)
	{
		menuItem->setTag(TAG_MENU_START);
	}
	else if (strcmp(pszType, STR_MENU_SETTINGS) == 0)
	{
		menuItem->setTag(TAG_MENU_SETTINGS);
	}
	else if (strcmp(pszType, STR_MENU_HELP) == 0)
	{
		menuItem->setTag(TAG_MENU_HELP);
	}
	else if (strcmp(pszType, STR_MENU_ABOUT) == 0)
	{
		menuItem->setTag(TAG_MENU_ABOUT);
	}
	else
	{
		//ERROR 
		CCLog("Unexpected branch visited in MenuLayer::getRandomMenuItem");
	}
	return menuItem;
}

void MenuLayer::menuCallback(CCObject* sender)
{
	CCMenuItem* item = dynamic_cast<CCMenuItem*>(sender);
	int tag = item->getTag();
	switch (tag)
	{
	case TAG_MENU_START:
		CCLog("MENU_START got"); 
		CCLog("Switch to hero selection...");
		// switch to map scene to show levels

		CCDirector::sharedDirector()->replaceScene(DistrictSelectScene::create());

		break;
	case TAG_MENU_SETTINGS:
		CCLog("MENU_SETTINGS got");
		// switch to settings scene
		CCNotificationCenter::sharedNotificationCenter()->postNotification("LUA TEST MSG", CCLayer::create());
		break;
	case TAG_MENU_HELP:
		CCLog("MENU_HELP got");
		// switch to help scene
		CCNotificationCenter::sharedNotificationCenter()->postNotification("LUA TEST MSG");
		break;
	case TAG_MENU_ABOUT:
		CCLog("MENU_ABOUT got");
		CCScriptEngineManager::sharedManager()->getScriptEngine()->executeScriptFile("registerNotification.lua");
		// switch to about scene
		break;
	}
}