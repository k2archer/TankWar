
#include "Enemy.h"
#include "types.h"

#include <ctime>
#include <cstdlib>

Enemy::Enemy() :
	_gun(nullptr),
	_alarmOn(false),
	_fireAlarmOn(false),
	_gunDirection(DOWN),
	iSpeed(2)
{

}

Enemy* Enemy::create(
	CCTMXTiledMap* map,
	const char* pszFileName,
	const char* objectPointName)
{
	
	Enemy *pRet = new(std::nothrow) Enemy();

	CCSprite* sprite = CCSprite::create(pszFileName);
	sprite->setScale(map->getTileSize().width / sprite->getContentSize().width);

	TMXObjectGroup* objectGroup = map->getObjectGroup("hero");
	ValueMap object = objectGroup->getObject(objectPointName);
	CCPoint point;
	point.x = object.at("x").asInt();
	point.y = object.at("y").asInt();
	pRet->setPosition(ccp(point.x, point.y));
	// ����������λ��

	pRet->bindSprite(sprite);

	pRet->bindTiledMap(map);

	//map->addChild(pRet);
	//pRet->setTag(110);
	//pRet->setOwner(ENEMY);

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Enemy::init()
{
	bool bRet = false;
	do {
		this->scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}

void Enemy::fire()
{
	if (_gun != nullptr) {
		DIRECTION direction = getDirection();
		_gun->fire(getPosition(), direction);
	}

}

void Enemy::timeTure(float dt)
{
	_alarmOn = false;
	//CCLOG("called timeTure");
	
	this->fire();
	
	srand(time(NULL) + (int)this);

	setiSpeed(2);
	changeDirection(DIRECTION(rand() % 4));
}

void Enemy::update(float delta)
{
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)    
//	if (KEY_DOWN(VK_K) && !this->key[K_LCONTROL])
//	{
//		//CCLOG("VK_LCONTROL VK_DOWN");
//		this->fire();
//		this->key[K_LCONTROL] = 1;
//	}
//	if (KEY_UP(VK_K) && this->key[K_LCONTROL])
//	{
//		//CCLOG("VK_LCONTROL VK_DOWN");
//		this->key[K_LCONTROL] = 0;
//	}
//
//	if (KEY_DOWN(VK_S) && !this->key[K_DOWN])
//	{
//		//CCLOG("KEY_UP VK_DOWN");
//		_iSpeed = 2;
//		changeDirection(DOWN);
//		this->key[K_DOWN] = 1;
//	}
//	if (KEY_UP(VK_S) && this->key[K_DOWN])
//	{
//		//CCLOG("KEY_UP VK_DOWN");
//		_iSpeed = 0;
//		_iDirection.x = 0;
//		_iDirection.y = 0;
//		this->key[K_DOWN] = 0;
//	}
//
//	if (KEY_DOWN(VK_W) && !this->key[K_UP])
//	{
//		//CCLOG("KEY_DOWN VK_DOWN");
//		_iSpeed = 2;
//		changeDirection(UP);
//		this->key[K_UP] = 1;
//	}
//	if (KEY_UP(VK_W) && this->key[K_UP])
//	{
//		//CCLOG("KEY_UP VK_DOWN");
//		_iSpeed = 0;
//		_iDirection.x = 0;
//		_iDirection.y = 0;
//		this->key[K_UP] = 0;
//	}
//
//	if (KEY_DOWN(VK_A) && !this->key[K_LEFT])
//	{
//		//CCLOG("KEY_DOWN VK_LEFT");
//		_iSpeed = 2;
//		changeDirection(LEFT);
//		this->key[K_LEFT] = 1;
//	}
//	if (KEY_UP(VK_A) && this->key[K_LEFT])
//	{
//		//CCLOG("KEY_UP VK_LEFT");
//		_iSpeed = 0;
//		_iDirection.x = 0;
//		_iDirection.y = 0;
//		this->key[K_LEFT] = 0;
//	}
//
//	if (KEY_DOWN(VK_D) && !this->key[K_RIGHT])
//	{
//		//CCLOG("KEY_DOWN VK_RIGHT");
//		_iSpeed = 2;
//		changeDirection(RIGHT);
//		this->key[K_RIGHT] = 1;
//	}
//	if (KEY_UP(VK_D) && this->key[K_RIGHT])
//	{
//		//CCLOG("KEY_UP VK_RIGHT");
//		_iSpeed = 0;
//		_iDirection.x = 0;
//		_iDirection.y = 0;
//		this->key[K_RIGHT] = 0;
//	}
//
//#endif


	CCPoint curPos = getPosition();
	curPos += _iDirection;

	setPosition(curPos);

	if (!_alarmOn) {
		srand(time(NULL) + (int)this);
		float time = rand() % 5 + 1;
		this->scheduleOnce(schedule_selector(Enemy::timeTure), time);
		_alarmOn = true;
	}
}

void Enemy::setPosition(const Vec2& dstPos)
{
	if (isConllsionTiled(dstPos.x, dstPos.y)) {
		return;
	}
	else if (isConllsion(dstPos.x, dstPos.y)) {
		return;
	}
	else if (isConllsionEnemy(dstPos.x, dstPos.y)) {
		return;
	}
	else if (isConllsionPlayer(dstPos.x, dstPos.y)) {
		return;
	}

	Entity::setPosition(dstPos);
}

bool Enemy::isConllsion(float x, float y)
{
	if (_sprite == nullptr)
		return false;

	for (int i = PLAYER_START_TAG; i < PLAYER_START_TAG + PLAYER_NUM + ENEMY_NUM; i++)
	{
		if (i == this->getTag())
			continue;

		Entity* p_entity = (Entity*)_map->getChildByTag(i);
		if (p_entity == nullptr)
			continue;

		CCPoint cc1 = _sprite->convertToNodeSpace(ccp(x, y));
		CCPoint cc2 = _sprite->convertToNodeSpace(p_entity->getPosition());
		int x1 = cc1.x - 32;
		int y1 = cc1.y - 32;
		int x2 = cc2.x - 32;
		int y2 = cc2.y - 32;
		if (isCollision(ccp(x1, y1), ccp(x2, y2), 16, 16, 16, 16))
		{
			if (p_entity->getOwner() == PLAYER )
				this->fire();

			switch (_gunDirection) {
			case UP: y -= iSpeed; changeDirection(RIGHT); return true;
			case DOWN: y += iSpeed; changeDirection(LEFT); return true;
			case LEFT: x += iSpeed; changeDirection(UP); return true;
			case RIGHT: x -= iSpeed; changeDirection(DOWN); return true;
			default: return true;
			}
		}
	}
	return false;
}

bool Enemy::isConllsionPlayer(float x, float y)
{
	if (_sprite == nullptr)
		return false;

	for (int i = PLAYER_START_TAG; i < PLAYER_START_TAG + PLAYER_NUM; i++)
	{
		if ( i == this->getTag())
			continue;

		Entity* p_entity = (Entity*) _map->getChildByTag(i);
		if ( p_entity == nullptr)
			continue;

		CCPoint cc1 = _sprite->convertToNodeSpace(ccp(x, y));
		CCPoint cc2 = _sprite->convertToNodeSpace(p_entity->getPosition());
		int x1 = cc1.x -32;
		int y1 = cc1.y -32;
		int x2 = cc2.x-32;
		int y2 = cc2.y-32;
		if ( isCollision( ccp( x1 , y1 ), ccp( x2, y2 ) , 16, 16, 16, 16))
		{
			if (p_entity->getOwner() == PLAYER )
				this->fire();

			switch (_gunDirection) {
			case UP : y -= iSpeed; changeDirection( RIGHT ); return true;
			case DOWN : y += iSpeed; changeDirection( LEFT ); return true;
			case LEFT : x += iSpeed; changeDirection( UP ); return true;
			case RIGHT : x -= iSpeed; changeDirection( DOWN ); return true;
			default: return true;
			}
		}
	}
	return false;
}

bool Enemy::isConllsionEnemy(float x, float y)
{
	if (_sprite == nullptr)
		return false;

	for (int i = ENEMY_START_TAG; i < ENEMY_START_TAG + 4 ; i++)
	{
		if ( i == this->getTag())
			continue;

		Entity* p_entity = (Entity*) _map->getChildByTag(i);
		if ( p_entity == nullptr)
			continue;

		CCPoint cc1 = _sprite->convertToNodeSpace(ccp(x, y));
		CCPoint cc2 = _sprite->convertToNodeSpace(p_entity->getPosition());
		int x1 = cc1.x -32;
		int y1 = cc1.y -32;
		int x2 = cc2.x-32;
		int y2 = cc2.y-32;
		if ( isCollision( ccp( x1 , y1 ), ccp( x2, y2 ) , 16, 16, 16, 16))
		{
			srand (time(NULL) + (int)this);
			switch (_gunDirection) {
			case UP : y -= iSpeed; changeDirection( RIGHT ); return true;
			case DOWN : y += iSpeed; changeDirection( LEFT ); return true;
			case LEFT : x += iSpeed; changeDirection( UP ); return true;
			case RIGHT : x -= iSpeed; changeDirection( DOWN ); return true;
			default: return true;
			}
		}
	}
	return false;
}

bool Enemy::isConllsionTiled(float x, float y)
{
	if (_sprite == nullptr)
		return false;

	CCSize spriteSize = _sprite->getContentSize();

	CCPoint dstPos[8];
	dstPos[0] = CCPoint(x + spriteSize.width / 2 + 2, y);		// left
	dstPos[1] = CCPoint(x + spriteSize.width - 2, y);		// right
	dstPos[2] = CCPoint(x + spriteSize.width - 2, y + spriteSize.height / 2 - 2);   // up
	dstPos[3] = CCPoint(x + spriteSize.width - 2, y - spriteSize.height / 2 + 2);   // down
	dstPos[4] = CCPoint(x + spriteSize.width / 2 + 2, y + spriteSize.height / 2 - 2);  // left+up
	dstPos[5] = CCPoint(x + spriteSize.width + 16 - 2, y + spriteSize.height / 2 - 2); // right+up
	dstPos[6] = CCPoint(x + spriteSize.width / 2 + 2, y - spriteSize.height / 2 + 2);  // left+down
	dstPos[7] = CCPoint(x + spriteSize.width + 16 - 2, y - spriteSize.height / 2 + 2);  // right+down

	for (int i = 0; i < 8; i++)
	{
		CCPoint tiledPos = tileCoordForPosition(ccp(dstPos[i].x, dstPos[i].y));
		CCTMXLayer* _mapBarriers = _map->layerNamed("barrier");
		int TiledGid = _mapBarriers->tileGIDAt(tiledPos);
		if (TiledGid != 0)
		{
			Value propertiesDict = _map->propertiesForGID(TiledGid);
			ValueMap valueMap = propertiesDict.asValueMap();
			if (!valueMap.empty()) {
				auto prop = valueMap["Wall"].asString();
				if ("true" == prop) {
					if (getDirection() == UP)
						changeDirection(LEFT);
					else if (getDirection() == RIGHT)
						changeDirection(UP);
					else if (getDirection() == DOWN)
						changeDirection(RIGHT);
					else if (getDirection() == LEFT)
						changeDirection(DOWN);
					return true;
				}

				prop = valueMap["Iron"].asString();
				if ("true" == prop) {
					if (getDirection() == UP) {
						srand(time(NULL) + (int)this);
						if ( rand() % 2 )
							changeDirection(LEFT);
						else
							changeDirection(RIGHT);
					}
					else if (getDirection() == RIGHT) {
						srand(time(NULL) + (int)this);
						if (rand() % 2)
							changeDirection(DOWN);
						else
							changeDirection(UP);
					}
					else if (getDirection() == DOWN) {
						srand(time(NULL) + (int)this);
						if (rand() % 2)
							changeDirection(RIGHT);
						else
							changeDirection(LEFT);
					}
					else if (getDirection() == LEFT) {
						srand(time(NULL) + (int)this);
						if (rand() % 2)
							changeDirection(DOWN);
						else
							changeDirection(UP);
					}
					return true;
				}

			}
		}
	}
	return false;
}

bool Enemy::isCollision(CCPoint p1, CCPoint p2, int w1, int h1, int w2, int h2)
{
	if (abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2) {
		return true;
	}
	return false;
}

CCPoint Enemy::tileCoordForPosition(CCPoint pos)
{
	//��ʽ1��
	int x1 = pos.x / _map->getContentSize().width * _map->getMapSize().width;
	int y1 = _map->getMapSize().height - pos.y / _map->getContentSize().height *_map->getMapSize().height;
	//bgLayer->getTileGIDAt(Point(x, y));
	//��ʽ2��
	int x2 = pos.x / _map->getTileSize().width;
	int y2 = (_map->getMapSize().height * _map->getTileSize().height - pos.y)
			/ _map->getTileSize().height;
	//bgLayer->getTileGIDAt(Point(x, y));

	if (x1 > 0)
		x1 -= 1;
	if (y1 > 0)
		y1 -= 0;
	return ccp(x1, y1);
}

void Enemy::changeDirection(DIRECTION x)
{
	CCTexture2D* texture = nullptr;
	_iSpeed = iSpeed;
	_gunDirection = x;

	switch (x) {
	case UP:
		setiXYSpeed(0, +_iSpeed);
		texture = CCTextureCache::sharedTextureCache()->addImage("green_tank_32x32_up.png");
		this->_sprite->setTexture(texture);
		return;
	case DOWN:
		setiXYSpeed(0, -_iSpeed);
		texture = CCTextureCache::sharedTextureCache()->addImage("green_tank_32x32_down.png");
		this->_sprite->setTexture(texture);
		return;
	case LEFT:
		setiXYSpeed(-_iSpeed, 0);
		texture = CCTextureCache::sharedTextureCache()->addImage("green_tank_32x32_left.png");
		this->_sprite->setTexture(texture);
		return;
	case RIGHT:
		setiXYSpeed(+_iSpeed, 0);
		texture = CCTextureCache::sharedTextureCache()->addImage("green_tank_32x32_right.png");
		this->_sprite->setTexture(texture);
		return;
	default:
		;
	}

	CCPoint curPos = getPosition();
	curPos += _iDirection;

	setPosition(curPos);

}

DIRECTION Enemy::getDirection()
{
	return _gunDirection;
}

void Enemy::bindTiledMap(CCTMXTiledMap* map)
{
	Entity::bindTiledMap( map );
	//_map->addChild(this);
}

void  Enemy::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags) 
{
	//glLineWidth(3);
	//	CCPoint curPos = getPosition();
	//	ccDrawColor4B(0,255,0,0); // set color 
	//	ccDrawRect(curPos, ccp(curPos.x + 32, curPos.y + 32));

	//auto array = PointArray::create(10);
	//ccDrawLine(Vec2(100, 100), Vec2(900, 100));
	//ccDrawRect(Vec2(100, 100), Vec2(100, 600));
	//array->addControlPoint(Vec2(100, 100));
	//ccDrawCardinalSpline(array, 0, 100);

		//CCPoint spritePos = _sprite->getPosition();

		//CCPoint cc1 = _map->convertToNodeSpace(ccp(curPos.x, curPos.y));
		//ccDrawColor4B(0, 128, 0, 0); // set color 
		//ccDrawRect(cc1, ccp(cc1.x + 32, cc1.y + 32));

		//CCPoint cc2 = this->convertToNodeSpace(ccp(x, y));
		//CCLOG("X=%f, Y=%f sX=%f, sY=%f xx=%f, yy=%f", curPos.x, curPos.y,
		//	spritePos.x, spritePos.y, x, y);

}

