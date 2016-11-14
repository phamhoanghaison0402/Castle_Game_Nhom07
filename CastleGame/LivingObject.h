#ifndef _LivingObject_H_
#define _LivingObject_H_

#include "DynamicObject.h"
#include "Collision.h"

class LivingObject : public DynamicObject, public Collision
{
public:
	bool _isDisappear; 
public:
	LivingObject(DXTexture *, D3DXVECTOR2, Direction = Direction::LEFT, D3DXVECTOR2 = D3DXVECTOR2(VELOCITY_NORMAL, VELOCITY_FAST));
	virtual void BeginToCheckCollisions();
	virtual CollisionDirection CheckCollisions(BaseObject *);
	virtual void ResponseCollisions();
	virtual void Draw(DXGame *pDXGame, Camera *pCamera);

	virtual void Die();
	virtual bool IsLive();
};

#endif