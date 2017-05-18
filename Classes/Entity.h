
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
USING_NS_CC;

#include "types.h"

class Entity : public CCNode
{
public:
	Entity();

	void setiSpeed(float iSpeed);
	void setiXSpeed(float iSpeed);
	void setiYSpeed(float iSpeed);
	void setiXYSpeed(float iXSpeed, float iYSpeed);

	virtual void bindTiledMap(CCTMXTiledMap* map);
	void bindSprite(CCSprite* sprite);

	void setOwner(OWNER owner);
	OWNER getOwner();

	float _iSpeed;
	CCPoint _iDirection;

	CCSprite* _sprite;
	CCTMXTiledMap* _map;

	OWNER _owner;
};

#endif // __ENTITY_H__
