#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "LivingObject.h"

class Enemy : public LivingObject
{
protected:
	D3DXVECTOR2 _maxV;
	bool _SFreeFall;
public:
	bool _isCollisionWithMario; 
	bool _isCollisionWithBullet;
public:
	Enemy(DXTexture *, D3DXVECTOR2, Direction = Direction::LEFT, D3DXVECTOR2 = D3DXVECTOR2(VELOCITY_NORMAL, VELOCITY_FAST));
	virtual void Update(GameTime *); // Update
	virtual void Draw(DXGame *, Camera *); // Vẽ
	virtual void UpdateObjectState(GameTime *);
	virtual void UpdateAnimation(); // Cập nhật frame animation

	virtual void CollisionWithMario();
	virtual void CollisionWithBullet();

	virtual void BeginToCheckCollisions();
	virtual void TopCol(BaseObject *obj);
	virtual void BottomCol(BaseObject *obj);
	virtual void LeftCol(BaseObject *obj);
	virtual void RightCol(BaseObject *obj);
	virtual CollisionDirection CheckCollisions(BaseObject *);
	virtual void ResponseCollisions();
};

#endif