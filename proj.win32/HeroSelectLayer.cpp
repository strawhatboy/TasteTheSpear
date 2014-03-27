#include "HeroSelectLayer.h"


HeroSelectLayer::HeroSelectLayer(void)
{
	INIT_POINTER(m_HerosIDs);
	m_HerosIDs = new vector<string>();
}


HeroSelectLayer::~HeroSelectLayer(void)
{
	CC_SAFE_DELETE(m_HerosIDs);
}

void HeroSelectLayer::onEnter()
{
	CCLayer::onEnter();


}

bool HeroSelectLayer::init()
{
	INIT_START

	CC_BREAK_IF(!CCLayer::init());
	auto typesLoader = GameObjectTypesLoader::sharedInstance();
	auto heros = typesLoader->getHeroTypes();
	auto arrLayer = CCArray::create();

	CCDictElement* el = NULL;
	int count = 0;
	CCDICT_FOREACH(heros, el)
	{
		auto herotype = dynamic_cast<HeroType*>(el->getObject());
		auto layer = getChildLayer(herotype);
		layer->setTag(count++);
		CC_CONTINUE_IF(layer == NULL);
		arrLayer->addObject(layer);
	}

	

	// adjust the screen
	auto pos = CCPDesignZero;
	auto scrollLayer = ScrollLayer::createWithLayers(arrLayer, CCSizeZero, pos);


	this->addChild(scrollLayer);
	scrollLayer->registerSelectEvent(this, callfuncO_selector(HeroSelectLayer::heroSelected));

		
		// Add Title Label
	CCLabelTTF* labelT = CCLabelTTF::create(GameDirector::sharedInstance()->getUIStringByID(10002).c_str(),
		"Segoe UI", 60.f, CCSizeMake(designResolutionSize.width, 100),
		kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
	labelT->setPosition(ccpAdd(CCPDesignZero, ccpSub(designResolutionSize, ccpMult(labelT->getContentSize(), 0.5f))));
	this->addChild(labelT);

	INIT_TRUE
	INIT_END
}

void HeroSelectLayer::heroSelected(CCObject* obj)
{	
	auto layer = dynamic_cast<CCLayer*>(obj);
	if (layer == NULL)
		return;

	int index = layer->getTag();
	auto heroID = this->m_HerosIDs->at(index);
	GameDirector::sharedInstance()->setCurrentHero(heroID);
	// move to game scene.
	auto gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
	CCLog("Hero Selected with index %d and id %s.", index, heroID.c_str());
}

CCLayer* HeroSelectLayer::getChildLayer(HeroType* heroType)
{
	auto typesLoader = GameObjectTypesLoader::sharedInstance();
	if (heroType == NULL)
		return NULL;

	CCLayer* layer = CCLayer::create();

	// Add armature 310 x 470
	auto armature = typesLoader->createArmatureByID(heroType->getTypeID().c_str());
	// put the armature in the layer.
	auto _1stPartPos = ccpSub(designResolutionSize, ccp(designResolutionSize.width, 100 + 300));
	armature->setPosition(ccpAdd(_1stPartPos, ccpMult(ccp(310, 300), 0.5)));
	armature->getAnimation()->play("standby");
	layer->addChild(armature);

	// Add Name Label
	CCLabelTTF* label = CCLabelTTF::create(heroType->getName().c_str(), "Segoe UI", 40.f,
		CCSizeMake(310, 300), kCCTextAlignmentLeft, kCCVerticalTextAlignmentBottom);
	label->setPosition(ccpAdd(armature->getPosition(), ccp(20, 20)));
	layer->addChild(label);

	// Add Description Label
	CCLabelTTF* labelD = CCLabelTTF::create(heroType->getDescription().c_str(), "Segoe UI", 30.f,
		CCSizeMake(designResolutionSize.width - 40, designResolutionSize.height - 300 -140),
		kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
	labelD->setPosition(ccpAdd(ccp(20, 20), ccpMult(labelD->getContentSize(), 0.5f)));
	layer->addChild(labelD);

	// Add Bars & Labels.
	CCLabelTTF* labelHP = CCLabelTTF::create(GameDirector::sharedInstance()->getUIStringByID(10007).c_str(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.6, 50), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelAttack = CCLabelTTF::create(GameDirector::sharedInstance()->getUIStringByID(10004).c_str(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.6, 50), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelDefense = CCLabelTTF::create(GameDirector::sharedInstance()->getUIStringByID(10005).c_str(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.6, 50), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelAttackSpeed = CCLabelTTF::create(GameDirector::sharedInstance()->getUIStringByID(10006).c_str(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.6, 50), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelHandle = CCLabelTTF::create(GameDirector::sharedInstance()->getUIStringByID(10008).c_str(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.6, 50), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);

	auto barLabelsPosX = designResolutionSize.width * 0.7;
	labelHP->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 50));
	labelAttack->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 100));
	labelDefense->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 150));
	labelAttackSpeed->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 200));
	labelHandle->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 250));

	layer->addChild(labelHP);
	layer->addChild(labelAttack);
	layer->addChild(labelDefense);
	layer->addChild(labelAttackSpeed);
	layer->addChild(labelHandle);

	auto heroLevel = UserDefaultUtils::sharedInstance()->getHeroLevel(heroType->getTypeID().c_str());
	auto heroLife = heroType->getLife() + (heroLevel - 1) * heroType->getLifeDelta();
	auto heroAttack = heroType->getAttack() + (heroLevel - 1) * heroType->getAttackDelta();
	auto heroDefense = heroType->getDefense() + (heroLevel - 1) * heroType->getDefenseDelta();
	auto heroFireRate = heroType->getFireRate() + (heroLevel - 1) * heroType->getFireRateDelta();
	
	barLabelsPosX = barLabelsPosX + designResolutionSize.width * 0.1;
	

	CCSpriteBatchNode* bars = CCSpriteBatchNode::create(LOADING_BAR_FILE_NAME);
	CCSprite* barHP = CCSprite::create(LOADING_BAR_FILE_NAME);
	CCSprite* barAttack = CCSprite::create(LOADING_BAR_FILE_NAME);
	CCSprite* barDefense = CCSprite::create(LOADING_BAR_FILE_NAME);
	CCSprite* barFireRate = CCSprite::create(LOADING_BAR_FILE_NAME);

	auto originBarSize = barHP->getContentSize();

	CCProgressTimer* progressbarHP = CCProgressTimer::create(barHP);
	CCProgressTimer* progressbarAttack = CCProgressTimer::create(barAttack);
	CCProgressTimer* progressbarbarDefense = CCProgressTimer::create(barDefense);
	CCProgressTimer* progressbarbarFireRate = CCProgressTimer::create(barFireRate);
	progressbarHP->setBarChangeRate(ccp(1, 0));
	progressbarHP->setMidpoint(ccp(0, 0.5));
	progressbarHP->setScaleX(designResolutionSize.width * 0.3 /originBarSize.width);
	progressbarHP->setType(kCCProgressTimerTypeBar);
	progressbarHP->setPercentage(heroLife);
	progressbarHP->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 50));
	progressbarHP->runAction(CCProgressFromTo::create(.2f, 0, heroLife));

	progressbarAttack->setBarChangeRate(ccp(1, 0));
	progressbarAttack->setBarChangeRate(ccp(1, 0));
	progressbarAttack->setMidpoint(ccp(0, 0.5));
	progressbarAttack->setScaleX(designResolutionSize.width * 0.3 /originBarSize.width);
	progressbarAttack->setType(kCCProgressTimerTypeBar);
	progressbarAttack->setPercentage(heroAttack);
	progressbarAttack->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 100));
	progressbarAttack->runAction(CCProgressFromTo::create(.2f, 0, heroAttack));

	progressbarbarDefense->setBarChangeRate(ccp(1, 0));
	progressbarbarDefense->setBarChangeRate(ccp(1, 0));
	progressbarbarDefense->setMidpoint(ccp(0, 0.5));
	progressbarbarDefense->setScaleX(designResolutionSize.width * 0.3 /originBarSize.width);
	progressbarbarDefense->setType(kCCProgressTimerTypeBar);
	progressbarbarDefense->setPercentage(heroDefense);
	progressbarbarDefense->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 150));
	progressbarbarDefense->runAction(CCProgressFromTo::create(.2f, 0, heroDefense));

	progressbarbarFireRate->setBarChangeRate(ccp(1, 0));
	progressbarbarFireRate->setBarChangeRate(ccp(1, 0));
	progressbarbarFireRate->setMidpoint(ccp(0, 0.5));
	progressbarbarFireRate->setScaleX(designResolutionSize.width * 0.3 /originBarSize.width);
	progressbarbarFireRate->setType(kCCProgressTimerTypeBar);
	progressbarbarFireRate->setPercentage(heroFireRate);
	progressbarbarFireRate->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 200));
	progressbarbarFireRate->runAction(CCProgressFromTo::create(.2f, 0, heroFireRate));



	bars->addChild(barHP);
	bars->addChild(barAttack);
	bars->addChild(barDefense);
	bars->addChild(barFireRate);

	//layer->addChild(bars);
	layer->addChild(progressbarHP);
	layer->addChild(progressbarAttack);
	layer->addChild(progressbarbarDefense);
	layer->addChild(progressbarbarFireRate);


	CCLabelTTF* labelHP_Value = CCLabelTTF::create(CCString::createWithFormat("%.1f",
		heroLife + (heroLevel - 1) * heroType->getLifeDelta())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelAttack_Value = CCLabelTTF::create(CCString::createWithFormat("%.1f",
		heroAttack + (heroLevel - 1) * heroType->getAttackDelta())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelDefense_Value = CCLabelTTF::create(CCString::createWithFormat("%.1f",
		heroDefense + (heroLevel - 1) * heroType->getDefenseDelta())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelAttackSpeed_Value = CCLabelTTF::create(CCString::createWithFormat("%.1f",
		heroFireRate + (heroLevel - 1) * heroType->getFireRateDelta())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	//CCLabelTTF* labelHandle_Value = CCLabelTTF::create(CCString::createWithFormat("%d",
	//	heroType->getHandling())->getCString(),
	//	"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.6, 50), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);

	//auto newBarLabelsPosX = designResolutionSize.width * 0.7


	labelHP_Value->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 50));
	labelAttack_Value->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 100));
	labelDefense_Value->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 150));
	labelAttackSpeed_Value->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 200));
	//labelHandle_Value->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 250));

	CCLabelTTF* labelHP_Value_Alpha = CCLabelTTF::create(CCString::createWithFormat("+%.1f",
		heroType->getLifeDelta())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelAttack_Value_Alpha = CCLabelTTF::create(CCString::createWithFormat("+%.1f",
		heroType->getAttackDelta())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelDefense_Value_Alpha = CCLabelTTF::create(CCString::createWithFormat("+%.1f",
		heroType->getDefenseDelta())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelAttackSpeed_Value_Alpha = CCLabelTTF::create(CCString::createWithFormat("+%.1f",
		heroType->getFireRateDelta())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
	CCLabelTTF* labelHandle_Value_Alpha = CCLabelTTF::create(CCString::createWithFormat("%d",
		heroType->getHandling())->getCString(),
		"Segoe UI", 25.f, CCSizeMake(designResolutionSize.width * 0.3, 50), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);

	labelHP_Value_Alpha->setColor(ccc3(0, 255, 0));
	labelAttack_Value_Alpha->setColor(ccc3(0, 255, 0));
	labelDefense_Value_Alpha->setColor(ccc3(0, 255, 0));
	labelAttackSpeed_Value_Alpha->setColor(ccc3(0, 255, 0));

	labelHP_Value_Alpha->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 50));
	labelAttack_Value_Alpha->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 100));
	labelDefense_Value_Alpha->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 150));
	labelAttackSpeed_Value_Alpha->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 200));
	labelHandle_Value_Alpha->setPosition(ccp(barLabelsPosX, designResolutionSize.height - 100 - 250));

	layer->addChild(labelHP_Value);
	layer->addChild(labelAttack_Value);
	layer->addChild(labelDefense_Value);
	layer->addChild(labelAttackSpeed_Value);
	//layer->addChild(labelHandle_Value);

	layer->addChild(labelHP_Value_Alpha);
	layer->addChild(labelAttack_Value_Alpha);
	layer->addChild(labelDefense_Value_Alpha);
	layer->addChild(labelAttackSpeed_Value_Alpha);
	layer->addChild(labelHandle_Value_Alpha);


	//vector<int> tmp;
	//tmp.push_back(labelHP->getContentSize().width);
	//tmp.push_back(labelAttack->getContentSize().width);
	//tmp.push_back(labelDefense->getContentSize().width);
	//tmp.push_back(labelAttackSpeed->getContentSize().width);
	//tmp.push_back(labelHandle->getContentSize().width);
	//auto maxElement = max_element(tmp.begin(), tmp.end());
	//auto maxWidth = *maxElement;

	//auto widthLeft = designResolutionSize.width - 

	m_HerosIDs->push_back(heroType->getTypeID());

	return layer;
}