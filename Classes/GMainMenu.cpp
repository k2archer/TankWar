
#include "GMainMenu.h"
#include "cocos2d.h"
USING_NS_CC;

#include "FirstBattle.h"
#include "AppDelegate.h"

CCScene* GMainMenu::createScene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GMainMenu *layer = GMainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GMainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() ) {
		return false;
	}
	bool bRet = false;
	do {
		CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		CCSprite* cocosImage = CCSprite::create("battle_city.png");
		cocosImage->setPosition(Vec2(visibleSize.width/2 + origin.x, 
								(visibleSize.height/2 + visibleSize.height/6) + origin.y));		
		this->addChild(cocosImage, 2);

		// CCMenuItemImage* pStartItem = CCMenuItemImage::create(
		// 	NULL,NULL, this, menu_selector(GMainMenu::menuStartCallback));

		CCLabelTTF* _1_player_labe1 = CCLabelTTF::create("1  Player", "Arial", 30);
		CCMenuItemLabel* p_1_player_item = CCMenuItemLabel::create(
			_1_player_labe1, this,  menu_selector(GMainMenu::menu1PlayerCallback));

		CCLabelTTF* _2_player_labe1 = CCLabelTTF::create("2  Player", "Arial", 30);
		CCMenuItemLabel* p_2_player_item = CCMenuItemLabel::create(
			_2_player_labe1, this,  menu_selector(GMainMenu::menu2PlayerCallback));

		CCMenu* pMenu = CCMenu::create( p_1_player_item, p_2_player_item, NULL);

		pMenu->alignItemsVertically();

		pMenu->setPosition(Vec2(visibleSize.width/2 + origin.x, 
									visibleSize.height/3 + origin.y));
		this->addChild(pMenu, 1);
	
		bRet = true;
	}while(0);

	return bRet;
}

void GMainMenu::menuStartCallback(CCObject* pSender)
{
	//CCDirector::sharedDirector()->end();
	// AppDelegate* app = (AppDelegate *)CCApplication::sharedApplication();
	// GGameData* _curTest = app->getCurrentData();
	// _curTest->playerNum++;
	// CCDirector::sharedDirector()->replaceScene(FirstBattle::scene());
}


void GMainMenu::menu1PlayerCallback(CCObject* pSender)
{
	// AppDelegate* app = (AppDelegate *)CCApplication::sharedApplication();
	// GGameData* _curTest = app->getCurrentData();
	// _curTest->playerNum = 1;
	CCDirector::sharedDirector()->replaceScene(FirstBattle::scene());
}

void GMainMenu::menu2PlayerCallback(CCObject* pSender)
{
	// AppDelegate* app = (AppDelegate *)CCApplication::sharedApplication();
	// GGameData* _curTest = app->getCurrentData();
	// _curTest->playerNum = 2;
	// CCDirector::sharedDirector()->replaceScene(FirstBattle::scene());
}

