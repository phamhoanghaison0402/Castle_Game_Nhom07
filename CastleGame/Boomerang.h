#ifndef _Boomerang_H_
#define _Boomerang_H_

#include "DynamicObject.h"
#include "Collision.h"


class Boomerang : public DynamicObject, public Collision
{
private:
	D3DXVECTOR2 _a;
	D3DXVECTOR2 _maxV;
	bool _SFreeFall;
public:
	Boomerang(DXTexture *, D3DXVECTOR2, D3DXVECTOR2 = D3DXVECTOR2(500, 800), D3DXVECTOR2 = D3DXVECTOR2(1200, -6000));
	virtual void Update(GameTime *);
	virtual void Draw(DXGame *, Camera *);
	virtual void UpdateObjectState(GameTime *);
	virtual void UpdateAnimation();

	virtual void BeginToCheckCollisions();
	virtual void TopCol(BaseObject *obj);
	virtual void BottomCol(BaseObject *obj);
	virtual void LeftCol(BaseObject *obj);
	virtual void RightCol(BaseObject *obj);
	virtual CollisionDirection CheckCollisions(BaseObject *);
	virtual void ResponseCollisions();
};

#endif