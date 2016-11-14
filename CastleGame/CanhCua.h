#ifndef _CANHCUA_H_
#define _CANHCUA_H_

#include "DynamicObject.h"
#include "Collision.h"
#include <list>

class CanhCua : public DynamicObject, public Collision
{
public:
	DXTexture *_canhcuaTexture;
	D3DXCOLOR _color;

	D3DXVECTOR2 _temp;

public:
	bool _MoveLeft, _MoveRight;

public:
	CanhCua(
		DXTexture *pTexture,
		D3DXVECTOR2 position);

	virtual void Draw(DXGame *pDXGame, Camera *);
	virtual void Update(GameTime *);
	virtual void UpdateBound(); // cập nhật hình chữ nhật bao quanh đối tượng

	virtual CollisionDirection CheckCollisions(BaseObject *);
	virtual void ResponseCollisions();
};

#endif