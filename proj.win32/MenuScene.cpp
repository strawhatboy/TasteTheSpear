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

		// 1. New Game	"���ﲻ�ǿ�ʼ����" "�¤��ʁ��h" "��Ϲ�㣬����Ͷ���" "����Ϸ(ι��ôͻȻ��������)" "С�������İ�"
		// 2. Settings	"��Ҫ˫���ڣ�����" "������Чȥʺ�ɣ�����" "ħ�����𶯣�" "she zhi" "����" "��͢˹"
		// 3. Help		"��ʦ������" "\"ѧ���ҵ��Ի���\"" "�߾���������tm����ô��" "�Ҳ����������ô���" "����" "����Ұ�������û�Զ�����"
		// 4. About		"���ĸ�sx д����Ϸ" "��Ҫ�ٱ������в���г����" "������ǿ����į�����ֽ...����ϵ��!" "�P��L" "����Ĳ����˳�"
		/*vector<wstring> newGameStrings;
		newGameStrings.push_back(L"���ﲻ�ǿ�ʼ����");
		newGameStrings.push_back(L"�¤��ʁ��h");
		newGameStrings.push_back(L"��Ϲ�㣬����Ͷ���");
		newGameStrings.push_back(L"����Ϸ(ι��ôͻȻ��������)");
		newGameStrings.push_back(L"С�������İ�");

		vector<wstring> settingsStrings;
		settingsStrings.push_back(L"��Ҫ˫���ڣ�����");
		settingsStrings.push_back(L"������Чȥʺ�ɣ�����");
		settingsStrings.push_back(L"ħ�����𶯣�");
		settingsStrings.push_back(L"she zhi");
		settingsStrings.push_back(L"����");
		settingsStrings.push_back(L"��͢˹");

		vector<wstring> helpStrings;
		helpStrings.push_back(L"��ʦ������");
		helpStrings.push_back(L"\"ѧ���ҵ��Ի���\"");
		helpStrings.push_back(L"�߾���������tm����ô��");
		helpStrings.push_back(L"�Ҳ����������ô���");
		helpStrings.push_back(L"����");
		helpStrings.push_back(L"����Ұ�������û�Զ�����");

		vector<wstring> aboutStrings;
		aboutStrings.push_back(L"���ĸ�sx д����Ϸ");

		CCMenuItemFont* item = CCMenuItemFont::create(w2c(L"�߾���������tm����ô�棡��"), this, menu_selector(MenuScene::menuNewGameCallback));
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
		WStrToUTF8(L"�Բ���Ҳ̫�ӵ��˰��Բ���Ҳ̫�ӵ��˰��Բ���Ҳ̫�ӵ��˰��Բ���Ҳ̫�ӵ��˰��Բ���Ҳ̫�ӵ��˰��Բ���Ҳ̫�ӵ��˰��Բ���Ҳ̫�ӵ��˰ɣ�����@#%$#^%").c_str()
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