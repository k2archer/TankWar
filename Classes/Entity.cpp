
#include"Entity.h"

Entity::Entity():
	_map(nullptr),
	_sprite(nullptr)
{

}

void Entity::bindTiledMap(CCTMXTiledMap* map)
{
	_map = map;
	CC_SAFE_RETAIN(_map);
	//_map->addChild(this);
}

void Entity::bindSprite(CCSprite* sprite)
{
	_sprite = sprite;
	this->addChild(sprite);
}

void Entity::setiSpeed(float iSpeed)
{
	this->_iSpeed = iSpeed;
}

void Entity::setiXSpeed(float iSpeed)
{
	this->_iDirection.x = iSpeed;
}

void Entity::setiYSpeed(float iSpeed)
{
	this->_iDirection.y = iSpeed;
}

void Entity::setiXYSpeed(float iXSpeed, float iYSpeed)
{
	setiXSpeed(iXSpeed);
	setiYSpeed(iYSpeed);
}

void Entity::setOwner(OWNER owner)
{
	_owner = owner;
}

OWNER Entity::getOwner()
{
	return _owner;
}