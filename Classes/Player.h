
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Entity.h"
#include "Gun.h"
#include "CControl.h"

class Player : public Entity, public ControllerListener
{
public:
	/* 设置位置 */
	virtual void setTagPosition(float x, float y) {
		this->setPosition(ccp(x, y));
	}
	virtual Point getTagPosition() {
		return this->getPosition();
	}

	virtual void Cfire() {
		if (_gun != nullptr) {
			DIRECTION direction = getDirection();
			_gun->fire(getPosition(), direction);
		}
	}

	virtual void Cstop() {
		setiSpeed(0);
		setiXYSpeed(0, 0);
	}
	virtual void Crun() {
		_iSpeed = 2;
	}
	virtual void CchangeDirection(DIRECTION x) {
		changeDirection(x);
	}
	virtual Point getiDirection() {
		return _iDirection;
	}

	/* 设置对象控制器 */
	void setController(Controller * controller) {
		m_controller = controller;
		m_controller->setControllerListener(this); //给控制器，设置被控制的对象
	}
protected:
	Controller * m_controller;

public:
	Player();
	~Player();

	//CREATE_FUNC(Enemy);
	
	static Player* create(
		CCTMXTiledMap* map,
		const char* pszFileName,
		const char* objectPointName);

	virtual bool init();

	void fire();

	virtual void bindTiledMap(CCTMXTiledMap* map);

	//void timeTure(float dt);
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

	//bool  _fireAlarmOn;
	//bool _alarmOn;

	DrawNode* nDraw;

	DIRECTION _gunDirection;

	float iSpeed;

};

#endif // __PLAYER_H__
