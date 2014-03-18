#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "MenuScene.h"
#include "Fighter.h"
#include "MyLoadingLayer.h"
#include "GameDirector.h"
#include "userdefaultutils.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
		
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

void HelloWorld::moveToMenuScene(float time)
{
	do
	{
		// scene change code
		CCDirector* pDirector = CCDirector::sharedDirector();
		MenuScene* menu = MenuScene::create();
		CC_BREAK_IF(!menu);
		//CCTransitionFade* fade = CCTransitionFade::create(0.5f, menu);
		//pDirector->pushScene(fade);
		//menu->retain();
		LoadingScene::sharedInstance()->SetLoadingLayer(MyLoadingLayer::create());
		//pDirector->replaceScene(LoadingScene::sharedInstance());
		SceneManager::sharedInstance()->loadScene(menu);

		//this->unschedule(schedule_selector(HelloWorld::moveToMenuScene));
		CCLOG("Another scene~");

		// tutsau test
		
		//ShowTuTsauMsg(WStrToUTF8(L"WTFWTJFIDSJFSDLblablalbalblalballhahahahah нт╡ш").c_str());
	} while (0);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
   //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 //   CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
 //                                       "CloseNormal.png",
 //                                       "CloseSelected.png",
 //                                       this,
 //                                       menu_selector(HelloWorld::menuCloseCallback));
 //   
	//pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
 //                               origin.y + pCloseItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
 //   pMenu->setPosition(CCPointZero);
 //   this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    //
    //// position the label on the center of the screen
    //pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - pLabel->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
	// Change it to COCOS LOGO
    CCSprite* pSprite = CCSprite::create("Logo.png");
	pSprite->setScale(2.f);
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
	
		//CCSprite* plane = Fighter::create();
		//if (plane)
		//{
		//plane->setPosition(ccp(origin.x + visibleSize.width/2, 64.f));
		//addChild(plane);
		//}

	// load game type definations
	GameObjectTypesLoader::sharedInstance()->loadAllTypes();
	this->m_nArmaturesCount = 0;
	this->m_nArmaturesTotalCount = GameObjectTypesLoader::sharedInstance()->loadArmaturesAsync(this, schedule_selector(HelloWorld::loadArmaturesComplete));


	// move to main menu scene.
	// this->schedule(schedule_selector(HelloWorld::moveToMenuScene), 1.0f);
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox  ("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::loadArmaturesComplete(float dt)
{
	this->m_nArmaturesCount++;
	CCLog("Armature loaded %d and the expected count is %d", this->m_nArmaturesCount, this->m_nArmaturesTotalCount);
	if (this->m_nArmaturesCount == this->m_nArmaturesTotalCount)
	{
		loadArmaturesAllComplete();
	}
}

void HelloWorld::loadArmaturesAllComplete()
{
#ifdef DEBUG
	auto hero = GameObjectTypesLoader::sharedInstance()->getHeroTypeByID("H001");
	CCLog("Hero H001's attack is %f", hero->getAttack());
	CCLog("Hero H001's attack delta is %f", hero->getAttackDelta());
	CCLog("Hero H001's life is %f", hero->getLife());
	
	CCLog("Hero H001's life delta is %f", hero->getLifeDelta());
#endif


	
	// load UserDefaults
	loadUserDefaults();

	// move to the next scene.
	//moveToMenuScene(0);
	// set gamestate to MainMenu.
	//GameDirector::sharedInstance()->setGameState(GameState::MAIN_MENU);
	//GameDirector::sharedInstance()->setGameState(MAIN_MENU);
	GameDirector::sharedInstance()->changeState(MAIN_MENU);
}

void HelloWorld::loadUserDefaults()
{
	auto userDefault = UserDefaultUtils::sharedInstance();
	if (!userDefault->isUserDefaultInitialized())
	{
		// set 1st run to true until we show the tutsau msg about the 1st time playing.
		userDefault->setFirstRun(true);

		auto typesLoader = GameObjectTypesLoader::sharedInstance();
		// set all district locked except for the 1st one.
		auto districts = typesLoader->getDistrictTypes();
		CCDictElement* el = NULL;
		CCDICT_FOREACH(districts, el)
		{
			auto district = dynamic_cast<DistrictType*>(el->getObject());


			CC_CONTINUE_IF(district == NULL);

			// the 1st one
			if(district->getTypeID() != "D001")
				userDefault->setDistrictUnlocked(district->getTypeID().c_str(), false);

			// set its LEVELs to locked.
			auto levels = district->getLevels();
			for_each(levels->begin(), levels->end(), [userDefault](const LevelType* levelType){
				if (levelType->getTypeID() != "L001")
				{
					userDefault->setLevelUnlocked(levelType->getTypeID().c_str(), false);
				}
			});
		}

		// set all heros' level to 1
		auto heros = typesLoader->getHeroTypes();
		el = NULL;
		CCDICT_FOREACH(heros, el)
		{
			auto hero = dynamic_cast<HeroType*>(el->getObject());

			CC_CONTINUE_IF(hero == NULL);

			userDefault->setHeroLevel(hero->getTypeID().c_str(), 1);
		}
	}
}