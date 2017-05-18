#ifndef __BULLET_H__
#define __BULLET_H__

#include "Entity.h"
#include "cocos2d.h"
#include "types.h"

USING_NS_CC;

enum { BULLET_NUM = 80 };

class Bullet : public Entity
{
public:
	Bullet();

	CREATE_FUNC(Bullet);
	
	bool init();
	
	void update(float delta);

	void fire(CCPoint point, float x, float y);

	void setTexture(const char *pzTexture);

	CCTexture2D* _texture;

	int _bulletNum;
	CCSprite* _sprite[BULLET_NUM];
	CCPoint  _spriteSpeed[BULLET_NUM];

	CCSpriteBatchNode* _batchNode;

	void bindBatchNode(const char* texturePngFile);

	bool isConllsionTarget(CCSprite* sprite, float x, float y);
	bool isCollisionTiled(CCSprite* sprite, CCPoint nextPos);
	
	CCPoint tileCoordForPosition(CCPoint pos);

};

#endif // __BULLET_H__