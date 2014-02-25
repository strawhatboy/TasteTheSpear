#pragma once
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include "cocos2d.h"
#include "AppMacros.h"

using namespace std;
USING_NS_CC;
//! convert from wstring to UTF8 using self-coding-converting


void WStrToUTF8(std::string& dest, const std::wstring& src);
std::string WStrToUTF8(const std::wstring& str);

// use unicode func
#define w2c(__wstring__) WStrToUTF8(__wstring__).c_str()



/**
@brief    The delegate of broadcast progress,
@param	minValue
@param	maxValue
@param	currentValue
*/
typedef void (CCObject::*SEL_BroadcastProgress)(int, int, int);
#define BROADCAST_PROGRESS(_SELECTOR) (SEL_BroadcastProgress)(&_SELECTOR)

#define CC_SHARED_CREATE_FUNC(__TYPE__) \
private:\
	static __TYPE__* m_sInstance;\
	__TYPE__(void);\
	class Garbo\
	{\
	public:\
		Garbo(void){};\
		~Garbo(void)\
		{\
			if (__TYPE__::m_sInstance)\
				delete __TYPE__::m_sInstance;\
		};\
	};\
	static Garbo __COLLECTOR;\
public:\
	inline static __TYPE__* sharedInstance(void)\
	{\
		if (m_sInstance == NULL)\
			m_sInstance = new __TYPE__();\
		if (m_sInstance)\
			return m_sInstance;\
		else\
			return NULL;\
	};

#define CC_SHARED_CREATE_IMPL(__TYPE__) __TYPE__* __TYPE__::m_sInstance = NULL

#define CC_CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        ((CCNode*)pRet)->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        CC_SAFE_DELETE(pRet); \
        return NULL; \
    } \
}



#define CREATE_WITH_DICT(__TYPE__)\
public:\
	__TYPE__(CCDictionary* dict);\
	static __TYPE__* createWithDict(CCDictionary* dict)\
	{\
		__TYPE__* pRet = new __TYPE__(dict);\
		if (pRet)\
			return pRet;\
		else\
		{\
			CC_SAFE_DELETE(pRet);\
		}\
		return NULL;\
	}

#define RUNTIME_OBJ_CREATE(__TYPE__, __OBJTYPE__)\
public:\
	static __TYPE__* createWith##__OBJTYPE__(__OBJTYPE__* type)\
	{\
		__TYPE__* pRet = new __TYPE__();\
		if (pRet && pRet->initWithGameObjectType(type))\
		{\
			pRet->autorelease();\
			return pRet;\
		}\
		else\
		{\
			CC_SAFE_DELETE(pRet);\
			return NULL;\
		}\
	}

#define CC_CREATE_FUNC_OBJ(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet) \
    { \
        return pRet; \
    } \
    else \
    { \
        CC_SAFE_DELETE(pRet); \
        return NULL; \
    } \
}

#define INIT_POINTER(__p) __p = NULL



#define DELETE_CPP_ARRAY(__PTR_ARRAY__, __ARRAY_TYPE__) \
	if (__PTR_ARRAY__ != NULL)\
	{\
		for_each(__PTR_ARRAY__->begin(), __PTR_ARRAY__->end(), [](__ARRAY_TYPE__* type)\
		{\
			CC_SAFE_DELETE(type);\
		});\
		CC_SAFE_DELETE(__PTR_ARRAY__);\
	}

#define CC_CONTINUE_IF(condition)\
	if (condition)\
		continue;

#define CCVisibleSize CCDirector::sharedDirector()->getVisibleSize()
#define CCVisibleOrigin CCDirector::sharedDirector()->getVisibleOrigin()
#define CCPCenterScreen ccpAdd(CCVisibleOrigin, ccpMult(CCVisibleSize, 0.5f))

// designResolutionSize is a static variable in AppMacro.h
#define CCPDesignZero ccpMult(ccpSub(CCVisibleSize, designResolutionSize), 0.5f)

//#define MAX(a, b) (((a) > (b)) ? (a) : (b))
//#define MIN(a, b) (((a) < (b)) ? (a) : (b))

//// 这里定义这么多宏也没问题么，不是说这样不好么
//#define FOLDER_TUTSAU "tutsau"
//#define STR_TUTSAU_FONTS "Tahoma"
//#define FONT_SIZE_TUTSAU 30
//#define TAG_TUTSAU 50
//#define STR_TUTSAU_FILE_SUFFIX ".png"
//#define STR_TUTSAU_TYPE_BUKENENG "bukeneng"
//#define STR_TUTSAU_TYPE_CAOx3 "caocaocao"
//#define STR_TUTSAU_TYPE_CAOx3_GINTOKI "caocaocao_gintoki"
//#define STR_TUTSAU_TYPE_CAOx3_KAGURA "caocaocao_kagura"
//#define STR_TUTSAU_TYPE_CAOx3_MEGANE "caocaocao_megane"
//#define STR_TUTSAU_TYPE_CAOx3_TSURA "caocaocao_tsura"
//#define STR_TUTSAU_TYPE_ERZHICHAN "erzhichan"
//#define STR_TUTSAU_TYPE_HEIx4 "heiheiheihei"
//#define STR_TUTSAU_TYPE_KENGDIE "kengdie"
//#define STR_TUTSAU_TYPE_KIMDAYE "kimdaye"
//#define STR_TUTSAU_TYPE_RENZHEN "renzhen"
//#define STR_TUTSAU_TYPE_WTF "wtf"
//#define STR_TUTSAU_TYPE_WTF2 "wtf2"
//#define STR_TUTSAU_TYPE_YAOMING "yaoming"
//#define STR_TUTSAU_TYPE_ZHENJING "zhenjing"
//#define STR_TUTSAU_TYPE_ZHUAI "zhuai"
//#define STR_TUTSAU_TYPE_WUGU "wugu"
//#define STR_TUTSAU_TYPE_MAMADAWO "mamadawo"
//#define STR_TUTSAU_TYPE_LOLOLO "lololo"
//
//
//
//// 随随便便加个全局函数什么的真的没问题么，破坏封装啊有木有！！
//// TuTsau, DONNOT use it unless the "runWithScene" of game director was called.
//bool ShowTuTsauMsg(const char* msg);
//bool ShowTuTsauMsg(const char* msgType, const char* msg);
//
//// load tu tsau msg from tutsau_config.plist and show it then mark it as shown.
//bool ShowTuTsauMsg(int msgID);
//// set force = true will ignore the msg that has been shown before.
//bool ShowTuTsauMsg(int msgID, bool force);


CCTexture2D* getEmptyWhiteTexture();