#ifndef CONST_APPDELEGATE
#define CONST_APPDELEGATE

#include "AppDelegate.h"

bool AppDelegate::applicationDidFinishLaunching()
{
	CCDirector* director 	= CCDirector::sharedDirector();
	CCEGLView*  EGLView 	= CCEGLView::sharedOpenGLView();
	CCSize 	screenSize 		= EGLView->getFrameSize();

	director->setOpenGLView(EGLView);
	//EGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
	director->setContentScaleFactor(380.0/320.0);

	vector <string> searchPath;

	if(screenSize.width > Resources1024x720.size.width && false)
	{
		searchPath.push_back(Resources2048x1536.directory);
		director->setContentScaleFactor(Resources2048x1536.size.height / designResolutionSize.height);
	}
	else if(screenSize.width > Resources480x320.size.width && false)
	{
		searchPath.push_back(Resources1024x720.directory);
		director->setContentScaleFactor(Resources1024x720.size.height / designResolutionSize.height);
	}
	else
	{
		searchPath.push_back(Resources480x320.directory);
		//director->setContentScaleFactor(MIN(Resources480x320.size.height / designResolutionSize.height, Resources480x320.size.width / designResolutionSize.width));
	}

	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

	Options::SCREEN_WIDTH  = designResolutionSize.width;
	Options::SCREEN_HEIGHT = designResolutionSize.height;

	Options::SCREEN_CENTER_X = designResolutionSize.width / 2;
	Options::SCREEN_CENTER_Y = designResolutionSize.height / 2;

	Options::CAMERA_WIDTH  = screenSize.width;
	Options::CAMERA_HEIGHT = screenSize.height;

	Options::CAMERA_CENTER_X  = screenSize.width / 2;
	Options::CAMERA_CENTER_Y = screenSize.height / 2;

	director->setDisplayStats(false);
	director->setAnimationInterval(1.0 / 60);

	Screen* pScene = new Preloader();

	director->runWithScene(pScene);
	
	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();
}

void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();
}

#endif