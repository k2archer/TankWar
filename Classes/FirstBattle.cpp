
#include "FirstBattle.h"
// #include "proj.win32/Controller.h"
// #include "proj.win32/PlayerContrller.h"
// #include "proj.win32/bullet.h"
// #include "proj.win32/config.h"

#include "cocos2d.h"
USING_NS_CC;

#include "Enemy.h"
#include "Player.h"
#include "AppDelegate.h"
#include "SimpleMoveController.h"

#include "TuchEventListener.h"

CCScene* FirstBattle::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FirstBattle *layer = FirstBattle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FirstBattle::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() ) {
        return false;
    }

	this->setMap("map.tmx");

	// AppDelegate* app = (AppDelegate *)CCApplication::sharedApplication();
	// GGameData* _curData = app->getCurrentData();
	// if ( _curData->playerNum == 1) {
		this->addPlayer("pink_tank_up.png", "player_1_point" );
	// } else if ( _curData->playerNum == 2) {
	// 	this->addPlayer(g_DefaultPlayerPngName, "player_1_point" );
	// 	this->addPlayer(g_DefaultPlayerPngName, "player_2_point" );
	// }

	 this->addEnemy("green_tank_32x32.png", "enemy_1" );
	 this->addEnemy("green_tank_32x32.png", "enemy_2" );
	 this->addEnemy("green_tank_32x32.png", "enemy_3" );
	 this->addEnemy("green_tank_32x32.png", "enemy_4" );
	
	// CCLOG("playerNum %d",_curData->playerNum);
	// CCLOG("playerNum %d",_curData->enemyNum);

	bool bRet = false;
	do {
		//this->schedule(schedule_selector(FirstBattle::update), 1.0f);
		bRet = true;
	}while(0);

    return true;
}

void FirstBattle::update(float delta)
{
	// AppDelegate* app = (AppDelegate *)CCApplication::sharedApplication();
	// GGameData* _curData = app->getCurrentData();
	// CCLOG("enemyNum %d",_curData->enemyNum);
	// if (_curData->enemyNum < 4) {
	// 	this->addEnemy("green_tank_32x32.png", "enemy_3" );
	// }
}

void FirstBattle::setMap(const char* mapName)
{
	this->_map = CCTMXTiledMap::create(mapName);
	//CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->_map->setPosition(Vec2(origin.x, origin.y));		
	this->addChild(this->_map);
}

CCPoint getOnMapPoint(CCTMXTiledMap* map, const char* pointNmae)
{
    TMXObjectGroup* objectGroup = map->getObjectGroup("hero");
    ValueMap object = objectGroup->getObject(pointNmae);

	CCPoint point;
	point.x = object.at("x").asInt();
	point.y = object.at("y").asInt();

	return point;
}

void FirstBattle::addPlayer(const char* pszFileName, const char* objectPointName)
{
	
	// ///////////////////////////// Add Player 
	Player* pPlayer = Player::create(_map, pszFileName, objectPointName);
	pPlayer->setOwner(PLAYER);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)    
	// 创建移动的控制器
	SimpleMoveController * MoveController = SimpleMoveController::create();
#else
	TuchEventListener* MoveController = TuchEventListener::create(this);
#endif
	MoveController->setSpeed(3);
	this->addChild(MoveController); //一定要添加到父节点，否则update不会调用
	pPlayer->setController(MoveController);


	if (pPlayer->_gun == nullptr) {
		pPlayer->_gun = new Gun();
		pPlayer->_gun->setOwner(PLAYER);
		pPlayer->_gun->bindTiledMap(_map);
		pPlayer->_gun->setFireSpeed(1);
		pPlayer->_gun->setBulletSpeed(2.5);

		Bullet* bullet = Bullet::create();
		bullet->setTexture("Terraria8x8.png");
		bullet->setOwner(PLAYER);
		bullet->bindTiledMap(_map);
		_map->addChild(bullet);

		pPlayer->_gun->bindBullet(bullet);
	}

	for (int i = PLAYER_START_TAG; ; i++) {
		if (_map->getChildByTag(i) == nullptr) {
			_map->addChild(pPlayer, 1, i);

			//AppDelegate* app = (AppDelegate *)CCApplication::sharedApplication();
			//GGameData* _curData = app->getCurrentData();
			//_curData->enemyNum ++;

			break;
		}
	}
	////CCSprite* playerSprite = CCSprite::create(pszFileName);

	////playerSprite->setScale(_map->getTileSize().width / playerSprite->getContentSize().width);

	////CCPoint point = getOnMapPoint(_map, objectPointName);
	////playerSprite->setPosition(ccp(point.x, point.y));

	////_map->addChild(playerSprite);
}

void FirstBattle::addEnemy(const char* pszFileName, const char* objectPointName)
{
	///////////////// add Enemy
	Enemy* pEnemy = Enemy::create(_map, pszFileName, objectPointName);
	pEnemy->setOwner(ENEMY);

	 if (pEnemy->_gun == nullptr) {
		 pEnemy->_gun = new Gun();
		 pEnemy->_gun->setOwner(ENEMY);
		 pEnemy->_gun->bindTiledMap(_map);
		 pEnemy->_gun->setFireSpeed(1);
		 pEnemy->_gun->setBulletSpeed(2);

		 Bullet* bullet = Bullet::create();
		 bullet->setTexture("Terraria8x8.png");
		 bullet->setOwner(ENEMY);
		 bullet->bindTiledMap(_map);
		 _map->addChild(bullet);

		 pEnemy->_gun->bindBullet(bullet);
	 }

	 for (int i = ENEMY_START_TAG; ; i++) {
	 	if (_map->getChildByTag(i) == nullptr) {
	 		_map->addChild(pEnemy, 1, i );

	 		//AppDelegate* app = (AppDelegate *)CCApplication::sharedApplication();
	 		//GGameData* _curData = app->getCurrentData();
	 		//_curData->enemyNum ++;

	 		break;
	 	}
	 }
	
}

void FirstBattle::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void  FirstBattle::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
	//CCPoint curPos = getPosition();
	//ccDrawColor4B(255, 0, 0, 0); // set color 
	//ccDrawRect(curPos, ccp(curPos.x + 35, curPos.y + 32));

	//auto array = PointArray::create(10);
	//ccDrawLine(Vec2(50, 50), Vec2(500, 500));
	////ccDrawLine(Vec2(100, 100), Vec2(100, 600));
	//array->addControlPoint(Vec2(100, 100));
	//ccDrawCardinalSpline(array, 0, 100);

}