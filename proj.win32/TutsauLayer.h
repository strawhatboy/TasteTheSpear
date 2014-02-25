#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "myLib.h"

USING_NS_CC;

using namespace CocosDenshion;

// 这里定义这么多宏也没问题么，不是说这样不好么
#define FOLDER_TUTSAU "tutsau"
#define STR_TUTSAU_FONTS "Tahoma"
#define FONT_SIZE_TUTSAU 30
#define TAG_TUTSAU 50
#define STR_TUTSAU_FILE_SUFFIX ".png"
#define STR_TUTSAU_TYPE_BUKENENG "bukeneng"
#define STR_TUTSAU_TYPE_CAOx3 "caocaocao"
#define STR_TUTSAU_TYPE_CAOx3_GINTOKI "caocaocao_gintoki"
#define STR_TUTSAU_TYPE_CAOx3_KAGURA "caocaocao_kagura"
#define STR_TUTSAU_TYPE_CAOx3_MEGANE "caocaocao_megane"
#define STR_TUTSAU_TYPE_CAOx3_TSURA "caocaocao_tsura"
#define STR_TUTSAU_TYPE_ERZHICHAN "erzhichan"
#define STR_TUTSAU_TYPE_HEIx4 "heiheiheihei"
#define STR_TUTSAU_TYPE_KENGDIE "kengdie"
#define STR_TUTSAU_TYPE_KIMDAYE "kimdaye"
#define STR_TUTSAU_TYPE_RENZHEN "renzhen"
#define STR_TUTSAU_TYPE_WTF "wtf"
#define STR_TUTSAU_TYPE_WTF2 "wtf2"
#define STR_TUTSAU_TYPE_YAOMING "yaoming"
#define STR_TUTSAU_TYPE_ZHENJING "zhenjing"
#define STR_TUTSAU_TYPE_ZHUAI "zhuai"
#define STR_TUTSAU_TYPE_WUGU "wugu"
#define STR_TUTSAU_TYPE_MAMADAWO "mamadawo"
#define STR_TUTSAU_TYPE_LOLOLO "lololo"

#define TOUCH_PRIORITY_MENU kCCMenuHandlerPriority
#define TOUCH_PRIORITY_TUTSAULAYER TOUCH_PRIORITY_MENU - 1

static void setEnableRecursiveCascading(CCNode* node, bool enable);

class TutsauLayer :
	public CCLayerColor
{
private:
	string m_imageFilePath;
	bool m_bIsInitWithMsgID;

	string m_msg;
	string m_msgType;

	int m_nMsgID;
	bool m_bForced;

	void delayRemoveSelf();

public:
	TutsauLayer(void);
	TutsauLayer(const char* msg);
	TutsauLayer(const char* msgType, const char* msg);
	TutsauLayer(int msgID);
	TutsauLayer(int msgID, bool force);
	~TutsauLayer(void);

	virtual bool init();

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();

	CREATE_FUNC(TutsauLayer);
	static TutsauLayer* create(const char* msg)
	{
		TutsauLayer* pRet = new TutsauLayer(msg);
		if (pRet && pRet->init())
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

	static TutsauLayer* create(const char* msgType, const char* msg)
	{
		TutsauLayer* pRet = new TutsauLayer(msgType, msg);
		if (pRet && pRet->init())
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

	static TutsauLayer* create(int msgID)
	{
		TutsauLayer* pRet = new TutsauLayer(msgID);
		if (pRet && pRet->init())
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

	static TutsauLayer* create(int msgID, bool force)
	{
		TutsauLayer* pRet = new TutsauLayer(msgID, force);
		if (pRet && pRet->init())
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
};

