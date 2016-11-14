#ifndef _NgonNen_H_
#define _NgonNen_H_

#include "DynamicObject.h"
#include "Collision.h"
#include <list>

class NgonNen : public DynamicObject, public Collision
{
public:
	DXTexture *_castleTexture;
	D3DXCOLOR _color;

	D3DXVECTOR2 _temp;
public:
	bool _isDea;

public:
	NgonNen(
		DXTexture *pTexture,
		D3DXVECTOR2 position);

	virtual void Draw(DXGame *pDXGame, Camera *);
	virtual void Update(GameTime *);
	virtual void UpdateAnimation();

	virtual CollisionDirection CheckCollisions(BaseObject *);
	virtual void ResponseCollisions();
};

#endif