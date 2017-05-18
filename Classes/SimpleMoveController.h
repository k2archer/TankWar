
#ifndef __SIMPLECONTROLLER_H__
#define __SIMPLECONTROLLER_H__

#include "cocos2d.h"
USING_NS_CC;
#include "CControl.h"
#include "types.h"

class SimpleMoveController : public Controller
{
public:
    CREATE_FUNC(SimpleMoveController);
    virtual bool init();

    virtual void update(float dt);  // schedualUpdate();

    void setSpeed(int iSpeed);

private:
    int m_iSpeed;

	int key[5];
	int keyNum;
};

// SimpleMoveController.cpp

bool SimpleMoveController::init()
{
    if (!Node::init())
        return false;

    /* 默认速度为0 */
    this->m_iSpeed = 0;

    /* 定时调用update */
    this->scheduleUpdate();

    return true;
}

void SimpleMoveController::update(float dt)
{
    if ( m_controllerListener == nullptr )
    {
        return;
    }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)    
	if (KEY_DOWN(VK_K) && !this->key[K_LCONTROL])
	{
		//CCLOG("VK_LCONTROL VK_DOWN");
		m_controllerListener->Cfire();
		this->key[K_LCONTROL] = 1;
	}
	if (KEY_UP(VK_K) && this->key[K_LCONTROL])
	{
		//CCLOG("VK_LCONTROL VK_DOWN");
		this->key[K_LCONTROL] = 0;
	}

	if (KEY_DOWN(VK_S) && !this->key[K_DOWN])
	{
		//CCLOG("KEY_UP VK_DOWN");
		m_controllerListener->Crun();
		m_controllerListener->CchangeDirection(DOWN);
		this->key[K_DOWN] = 1;
	}
	if (KEY_UP(VK_S) && this->key[K_DOWN])
	{
		//CCLOG("KEY_UP VK_DOWN");
		m_controllerListener->Cstop();
		this->key[K_DOWN] = 0;
	}

	if (KEY_DOWN(VK_W) && !this->key[K_UP])
	{
		//CCLOG("KEY_DOWN VK_DOWN");
		m_controllerListener->Crun();
		m_controllerListener->CchangeDirection(UP);
		this->key[K_UP] = 1;
	}
	if (KEY_UP(VK_W) && this->key[K_UP])
	{
		//CCLOG("KEY_UP VK_DOWN");
		m_controllerListener->Cstop();
		this->key[K_UP] = 0;
	}

	if (KEY_DOWN(VK_A) && !this->key[K_LEFT])
	{
		//CCLOG("KEY_DOWN VK_LEFT");
		m_controllerListener->Crun();
		m_controllerListener->CchangeDirection(LEFT);
		this->key[K_LEFT] = 1;
	}
	if (KEY_UP(VK_A) && this->key[K_LEFT])
	{
		//CCLOG("KEY_UP VK_LEFT");
		m_controllerListener->Cstop();
		this->key[K_LEFT] = 0;
	}

	if (KEY_DOWN(VK_D) && !this->key[K_RIGHT])
	{
		//CCLOG("KEY_DOWN VK_RIGHT");
		m_controllerListener->Crun();
		m_controllerListener->CchangeDirection(RIGHT);
		this->key[K_RIGHT] = 1;
	}
	if (KEY_UP(VK_D) && this->key[K_RIGHT])
	{
		//CCLOG("KEY_UP VK_RIGHT");
		m_controllerListener->Cstop();
		this->key[K_RIGHT] = 0;
	}

#endif
    ///* 增加移动对象的x坐标值 */
    Point pos = m_controllerListener->getTagPosition();
    
	//pos.x += m_iSpeed;
	pos += m_controllerListener->getiDirection();
    
	///* 被控制的对象 */
    m_controllerListener->setTagPosition(pos.x, pos.y);

}

void SimpleMoveController::setSpeed(int iSpeed)
{
    this->m_iSpeed = iSpeed;
}

#endif // __SIMPLECONTROLLER_H__
