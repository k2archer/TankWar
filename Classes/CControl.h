
#ifndef __CCONTROL_H__
#define __CCONTROL_H__


#include "cocos2d.h"

USING_NS_CC;

class ControllerListener
{
public:
    /*  控制器希望控制 被控对象 的位置  */
    virtual void setTagPosition(float x, float y) = 0;
    virtual Point getTagPosition() = 0;
	virtual Point getiDirection() = 0;

	virtual void Cstop() = 0;
	virtual void Cfire() = 0;
	virtual void Crun() = 0;

	virtual void CchangeDirection(DIRECTION x) = 0;
};


// 控制器基类
class Controller : public Node
{
public:
	void setControllerListener(ControllerListener * c) {
		m_controllerListener = c;
	}

protected:
	ControllerListener * m_controllerListener;
};

#endif // __CCONTROL_H__
