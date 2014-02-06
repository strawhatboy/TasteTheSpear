#include "MenuScene.h"
#include "myLib.h"

MenuScene::MenuScene(void)
{
	CCLog("Menu scene created?!");
}


MenuScene::~MenuScene(void)
{
	CCLog("Menu scene deleted?!");
}

bool MenuScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		
		/*cocos2d::CCMenu* menu = CCMenu::create();
		menu->addChild(CCMenuItem::create(CCRANDOM_0_1()*/

		// 1. New Game	"这里不是开始！！" "新たな伝説" "别瞎点，点这就对了" "新游戏(喂怎么突然变正经了)" "小样新来的吧"
		// 2. Settings	"我要双管炮！！！" "渣渣音效去屎吧！！！" "魔法，勿动！" "she zhi" "设置" "赛廷斯"
		// 3. Help		"老师他打我" "\"学长我电脑坏了\"" "蛇精病啊，这tm还怎么玩" "我不会告诉你怎么玩的" "救命" "帮帮我吧我两天没吃东西了"
		// 4. About		"这哪个sx 写的游戏" "我要举报这里有不和谐内容" "如果你是空虚寂寞冷的妹纸...请联系我!" "關雲長" "这真的不是退出"
		/*vector<wstring> newGameStrings;
		newGameStrings.push_back(L"这里不是开始！！");
		newGameStrings.push_back(L"新たな伝説");
		newGameStrings.push_back(L"别瞎点，点这就对了");
		newGameStrings.push_back(L"新游戏(喂怎么突然变正经了)");
		newGameStrings.push_back(L"小样新来的吧");

		vector<wstring> settingsStrings;
		settingsStrings.push_back(L"我要双管炮！！！");
		settingsStrings.push_back(L"渣渣音效去屎吧！！！");
		settingsStrings.push_back(L"魔法，勿动！");
		settingsStrings.push_back(L"she zhi");
		settingsStrings.push_back(L"设置");
		settingsStrings.push_back(L"赛廷斯");

		vector<wstring> helpStrings;
		helpStrings.push_back(L"老师他打我");
		helpStrings.push_back(L"\"学长我电脑坏了\"");
		helpStrings.push_back(L"蛇精病啊，这tm还怎么玩");
		helpStrings.push_back(L"我不会告诉你怎么玩的");
		helpStrings.push_back(L"救命");
		helpStrings.push_back(L"帮帮我吧我两天没吃东西了");

		vector<wstring> aboutStrings;
		aboutStrings.push_back(L"这哪个sx 写的游戏");

		CCMenuItemFont* item = CCMenuItemFont::create(w2c(L"蛇精病啊，这tm还怎么玩！！"), this, menu_selector(MenuScene::menuNewGameCallback));
		CC_BREAK_IF(!item);
		CCMenu* menu = CCMenu::create(item, NULL);
		CC_BREAK_IF(!menu);
		addChild(menu);
		bRet = true;
		CCLog("Added menu...");

*/
		//CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		//spriteFrameCache->addSpriteFramesWithFile("menu_items.plist");	
		//CCSprite* sprite_Start = CCSprite::createWithSpriteFrame(
		//	spriteFrameCache->spriteFrameByName("start_002.png"));
		//CCSprite* sprite_Start_Selected = CCSprite::createWithSpriteFrame(
		//	spriteFrameCache->spriteFrameByName("start_002_selected.png"));
		//CCSprite* sprite_About = CCSprite::createWithSpriteFrame(
		//	spriteFrameCache->spriteFrameByName("about_001.png"));
		//CCSprite* sprite_About_Selected = CCSprite::createWithSpriteFrame(
		//	spriteFrameCache->spriteFrameByName("about_001_selected.png"));
		//CCMenuItemSprite* menuItem_Start = CCMenuItemSprite::create(sprite_Start, sprite_Start_Selected, NULL, this, menu_selector(MenuScene::menuNewGameCallback));
		//CC_BREAK_IF(!menuItem_Start);
		//CCMenuItemSprite* menuItem_About = CCMenuItemSprite::create(sprite_About, sprite_About_Selected, NULL, this, menu_selector(MenuScene::menuNewGameCallback));
		//CC_BREAK_IF(!menuItem_About);
		//CCMenu* menu = CCMenu::create(menuItem_Start, NULL);
		//CC_BREAK_IF(!menu);
		//menu->addChild(menuItem_About);
		//menu->alignItemsVerticallyWithPadding(10.0);
		//addChild(menu);


		bRet = true;
		CCLog("Added menu...");
	} while(0);

	return bRet;
}

void MenuScene::onEnter()
{
	CCNode::onEnter();
	this->schedule(schedule_selector(MenuScene::testTuTsau), 2.0f);
	CCLog("Added schedule... in MenuScene::onEnter ");
}

bool MenuScene::drawContents()
{
	this->addChild(MenuLayer::create());
	return true;
}

void MenuScene::testTuTsau(float elapsedTime)
{
	unschedule(schedule_selector(MenuScene::testTuTsau));
	CCDirector::sharedDirector()->getRunningScene()->addChild(
		TutsauLayer::create(
		STR_TUTSAU_TYPE_HEIx4, 
		WStrToUTF8(L"卧槽这也太坑爹了吧卧槽这也太坑爹了吧卧槽这也太坑爹了吧卧槽这也太坑爹了吧卧槽这也太坑爹了吧卧槽这也太坑爹了吧卧槽这也太坑爹了吧！！！@#%$#^%").c_str()
		));
}

bool MenuScene::loadResources()
{
	bool bRet = false;

	auto loadingScene = LoadingScene::sharedInstance();
	/*this->setMinValue(0);
	this->setMaxValue(12);
	this->setCurrentValue(0);
*/
	this->m_progress->setMaxValue(3);
	this->m_progress->setMinValue(0);
	this->m_progress->setCurrentValue(0);
	LoadingScene::sharedInstance()->setProgress(this->m_progress);
	CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items.png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(1).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(2).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(3).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(4).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(5).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(6).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(7).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(8).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(9).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(10).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	//CCTextureCache::sharedTextureCache()->addImageAsync("menu_items(11).png", this, callfuncO_selector(MenuScene::resourceLoadedCallback));
	return true;

	return bRet;
}

void MenuScene::menuNewGameCallback(CCObject* sender)
{

}

void MenuScene::resourceLoadedCallback(CCObject *obj)
{
	UNREFERENCED_PARAMETER(obj);
	this->m_progress->setCurrentValue(this->m_progress->getCurrentValue() + 1);
	LoadingScene::sharedInstance()->setProgress(this->m_progress);
	//CCLog("%f %%", LoadingScene::sharedInstance()->getFinishPercentage() * 100);
}