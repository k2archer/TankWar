
#ifndef __GUN_H__
#define __GUN_H__

#include "Bullet.h"
#include "cocos2d.h"
USING_NS_CC;

class Gun
{
public:
	Gun();

	//CREATE_FUNC(Gun);

	bool init();

	void fire(CCPoint point, DIRECTION direction);

	void setOwner(OWNER owner);
	void bindBullet(Bullet* bullet);
	void setFireSpeed(float fireSpeed);
	void setBulletSpeed(float bulletSpeed);

	void bindTiledMap(CCTMXTiledMap* map);
	
	/* data */
	OWNER _owner;
	Bullet* _bullet;
	float _fireSpeed;
	float _bulletSpeed;

	CCTMXTiledMap* _map;
};

#endif // __GUN_H__