#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "AppMacros.h"

USING_NS_CC;

 // uncomment below line, open debug console
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#define USE_WIN32_CONSOLE
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
	int ret(0);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

	// set random seed
	cc_timeval psv;   
	CCTime::gettimeofdayCocos2d( &psv, NULL );    // 计算时间种子   
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;    // 初始化随机数   
	srand( tsrans ); 

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("Taste The Spear");
	eglView->setFrameSize(320, 480);
	//eglView->setFrameSize(768, 1366);
	//eglView->setFrameSize(768, 1024);
    //eglView->setFrameSize(1536, 2048);

    //eglView->setFrameSize(2048, 1536);
    // The resolution of ipad3 is very large. In general, PC's resolution is smaller than it.
    // So we need to invoke 'setFrameZoomFactor'(only valid on desktop(win32, mac, linux)) to make the window smaller.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    eglView->setFrameZoomFactor(1.5f);
#endif
    ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
