#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "BaseObject.h"
#include "DynamicObject.h"
#include "Factory.h"


/*
Xác định hướng xác định phía va chạm. NONE thể hiện không có va chạm.
*/
enum CollisionDirection
{
	NONE_COL = 0,
	LEFT_COL,
	TOP_COL,
	RIGHT_COL,
	BOTTOM_COL
};

class Collision
{
protected:
	float _moveX, _moveY;
	int _flagCollisionX, _flagCollisionY;
public:
	Collision();
	virtual void BeginToCheckCollisions();
	virtual void TopCol(BaseObject *obj);
	virtual void BottomCol(BaseObject *obj);
	virtual void LeftCol(BaseObject *obj);
	virtual void RightCol(BaseObject *obj);
	virtual CollisionDirection CheckCollisions(BaseObject *) = 0;
	CollisionDirection CheckCollisions(DynamicObject *, BaseObject *);
	virtual void ResponseCollisions() = 0;
	virtual D3DXVECTOR2 TransferPosition(D3DXVECTOR2 &);
};

#endif