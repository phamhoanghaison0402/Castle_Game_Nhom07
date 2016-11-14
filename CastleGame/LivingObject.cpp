#include "LivingObject.h"


LivingObject::LivingObject(DXTexture *pTexture, D3DXVECTOR2 position, Direction direction, D3DXVECTOR2 velocity)
	: DynamicObject(pTexture, position, direction, velocity), Collision()
{
	this->_isDisappear = false;
}

void LivingObject::BeginToCheckCollisions()
{
	Collision::BeginToCheckCollisions();
}

CollisionDirection LivingObject::CheckCollisions(BaseObject *obj)
{
	return Collision::CheckCollisions(this, obj);
}

void LivingObject::ResponseCollisions()
{
	Collision::TransferPosition(_position);
}

void LivingObject::Die()
{
	_isDead = true;
}

void LivingObject::Draw(DXGame *pDXGame, Camera *pCamera)
{
	if (!_isDisappear)
	{
		DynamicObject::Draw(pDXGame, pCamera);
	}
}

bool LivingObject::IsLive()
{
	return !_isDead;
}