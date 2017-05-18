
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Entity.h"
#include "Gun.h"

class Enemy : public Entity
{
public:
	Enemy();

	//CREATE_FUNC(Enemy);
	
	static Enemy* create(
		CCTMXTiledMap* map,
		const char* pszFileName,
		const char* objectPointName);

	virtual bool init();

	void fire();

	virtual void bindTiledMap(CCTMXTiledMap* map);

	void timeTure(float dt);
	virtual void update(float delta);

	bool isConllsion(float x, float y);
	bool isConllsionTiled(float x, float y);
	bool isConllsionEnemy(float x, float y);
	bool isConllsionPlayer(float x, float y);

	bool isCollision(CCPoint p1, CCPoint p2, int w1, int h1, int w2, int h2);
	CCPoint tileCoordForPosition(CCPoint pos);

	void changeDirection(DIRECTION x);
	DIRECTION getDirection();

	void setPosition(const Vec2& dstPos);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

	/* data */
	Gun* _gun;
	int key[5];
	int keyNum;

	bool  _fireAlarmOn;
	bool _alarmOn;

	DrawNode* nDraw;

	DIRECTION _gunDirection;

	float iSpeed;

};

#endif // __ENEMY_H__
