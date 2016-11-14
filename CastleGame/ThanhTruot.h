#ifndef _ThanhTruot_H_
#define _ThanhTruot_H_

#include "DynamicObject.h"
#include "Collision.h"
#include <list>

class ThanhTruot : public DynamicObject, public Collision
{
public:
	DXTexture *_castleTexture;
	D3DXCOLOR _color;

	D3DXVECTOR2 _temp;
	float _distance; // đoạn đường di chuyển

public:
	ThanhTruot(
		DXTexture *pTexture,
		D3DXVECTOR2 position,
		D3DXVECTOR2 velocity = D3DXVECTOR2(5, 5));

	virtual void Draw(DXGame *pDXGame, Camera *);
	virtual void Update(GameTime *);
	virtual void UpdateObjectState(GameTime *);
	virtual void UpdateMoving();

	virtual CollisionDirection CheckCollisions(BaseObject *);
	virtual void ResponseCollisions();
};

#endif