
#include "Bullet.h"

Bullet::Bullet() :
	_texture(NULL),
	_batchNode(NULL),
	_bulletNum(0)

{
	for (int i=0; i < BULLET_NUM; i++) {
		_sprite[i] = NULL;
		_spriteSpeed[i].x = 0;
		_spriteSpeed[i].y = 0;
	}
}

bool Bullet::init()
{

	bool bRet = false;
	do {
		this->scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}

void Bullet::update(float delta)
{
	for (int i=0; i < BULLET_NUM; i++) {
		if (_sprite[i] != NULL) {
			CCPoint spritePos = _sprite[i]->getPosition();
			CCPoint nextPos = spritePos + _spriteSpeed[i];
			
			// ////check bullet collision
			if (isCollisionTiled(_sprite[i], nextPos) )
			{ // collision with wall
				_batchNode->removeChild(_sprite[i], true);
				_sprite[i] = NULL;
				_bulletNum--;
				continue;
			}

			if (isConllsionTarget(_sprite[i], nextPos.x, nextPos.y) )
			{
				_batchNode->removeChild(_sprite[i], true);
				_sprite[i] = NULL;
				_bulletNum--;
				continue;
			}

			// set bullet fly
			_sprite[i]->setPosition(nextPos);
		}
	}
}

bool Bullet::isConllsionTarget(CCSprite* sprite, float x, float y)
{
	if (sprite == NULL)
		return false;

	for (int i = PLAYER_START_TAG; i < PLAYER_START_TAG + PLAYER_NUM + ENEMY_NUM; i++)
	{
		Entity* p_entity = (Entity*)_map->getChildByTag(i);
		if (p_entity == NULL)
			continue;

		if (p_entity != NULL && p_entity->getOwner() != this->getOwner()) {

			CCRect bullletRect = CCRectMake(
				x - (sprite->getContentSize().width / 2),
				y - (sprite->getContentSize().height / 2),
				sprite->getContentSize().width,
				sprite->getContentSize().height);

			CCRect targetRect = CCRectMake(
				p_entity->getPosition().x - (p_entity->_sprite->getContentSize().width / 2),
				p_entity->getPosition().y - (p_entity->_sprite->getContentSize().height / 2),
				p_entity->_sprite->getContentSize().width,
				p_entity->_sprite->getContentSize().height);

			if (targetRect.intersectsRect(bullletRect)) {
				_map->removeChild(p_entity);
				CCLOG("hit ..");
				return true;
			}
		}
	}
	return false;
}

bool Bullet::isCollisionTiled(CCSprite* sprite, CCPoint nextPos)
{
	CCPoint spritePos = sprite->getPosition();
	CCSize spriteSize = sprite->getContentSize();

	CCPoint dstPos[4];

	dstPos[0] = ccp(nextPos.x - 1.0, nextPos.y);	 // left
	dstPos[1] = ccp(nextPos.x + 1.0, nextPos.y);	 // right
	dstPos[2] = ccp(nextPos.x, nextPos.y - 1.0);   // up
	dstPos[3] = ccp(nextPos.x, nextPos.y + 1.0);   // down

	for(int i=0; i < 4; i++) 
	{
		CCPoint tiledPos = tileCoordForPosition(ccp(dstPos[i].x, dstPos[i].y));

		CCTMXLayer* mapBarriers = _map->layerNamed("barrier");

		int TiledGid = mapBarriers->tileGIDAt(tiledPos);
		if ( TiledGid != 0) {

			Value propertiesDict = _map->propertiesForGID(TiledGid);
			ValueMap valueMap = propertiesDict.asValueMap();
			if (!valueMap.empty()) {
				auto prop = valueMap["Wall"].asString();
				if ("true" == prop) {
					mapBarriers->removeTileAt(tiledPos);
					return true;
				}

				prop = valueMap["Iron"].asString();
				if ("true" == prop) {
					return true;
				}

				prop = valueMap["Heart"].asString();
				if ("true" == prop) {
				mapBarriers->removeTileAt(tiledPos);
				_iSpeed += 0.2f;
					return true;
				}
			}
		}
	}
	return false;
}

void Bullet::fire(CCPoint point, float x, float y)
{
	if (_bulletNum >= BULLET_NUM)
		return;

	CCSprite* sprite = CCSprite::createWithTexture(_texture);
	sprite->setPosition(point);
	_batchNode->addChild(sprite);
	
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(_fireMusicFile);

	for (int i=0; i < BULLET_NUM; i++) {
		if (_sprite[i] == NULL) {
			_sprite[i] = sprite;
			_spriteSpeed[i].x = x ;
			_spriteSpeed[i].y = y ;
			_bulletNum++;
			return;
		}
	}
}


CCPoint Bullet::tileCoordForPosition(CCPoint pos)
{
	//公式1：
	int x1 = pos.x / _map->getContentSize().width * _map->getMapSize().width;
	int y1 = _map->getMapSize().height - pos.y / _map->getContentSize().height *_map->getMapSize().height;
	//bgLayer->getTileGIDAt(Point(x, y));

	//公式2：
	int x2 = pos.x / _map->getTileSize().width;
	int y2 = (_map->getMapSize().height * _map->getTileSize().height - pos.y)
		/ _map->getTileSize().height;
	//bgLayer->getTileGIDAt(Point(x, y));

	return ccp(x1, y1);
}

void Bullet::setTexture(const char *texturePngFile)
{
	_texture = CCTextureCache::sharedTextureCache()->addImage(texturePngFile);
	bindBatchNode(texturePngFile);
}

void Bullet::bindBatchNode(const char* texturePngFile)
{
	if (_batchNode == NULL){
		_batchNode = CCSpriteBatchNode::create(texturePngFile);
		this->addChild(_batchNode);
	}
}

