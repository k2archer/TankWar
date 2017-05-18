
#include "Gun.h"

Gun::Gun() :
	_bullet(nullptr),
	_fireSpeed(0), 
	_bulletSpeed(0)
{

}

void Gun::fire(CCPoint point, DIRECTION direction)
{
	float x, y;

	switch(direction){
	case UP: 
		x = 0, y = + _bulletSpeed; break;
	case DOWN: 
		x = 0, y = - _bulletSpeed; break;
	case LEFT: 
		x = - _bulletSpeed, y = 0; break;
	case RIGHT: 
		x = + _bulletSpeed, y = 0; break;
	default:
		 x = 0, y = 0; return;
		;
	}
	if ( _bullet == nullptr) {
		_bullet = Bullet::create();
		_bullet->setOwner(_owner);
		_bullet->bindTiledMap(_map);
		_map->addChild(_bullet);
	}

	_bullet->fire(point, x, y);

}


void Gun::setOwner(OWNER owner)
{
	_owner = owner;
}

void Gun::bindBullet(Bullet* bullet)
{
	_bullet = bullet;
}

void Gun::setFireSpeed(float fireSpeed)
{
	_fireSpeed = fireSpeed;
}

void Gun::setBulletSpeed(float bulletSpeed)
{
	_bulletSpeed = bulletSpeed;
}

void Gun::bindTiledMap(CCTMXTiledMap* map)
{
	_map = map;
}
