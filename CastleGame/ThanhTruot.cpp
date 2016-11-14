#include "ThanhTruot.h"


ThanhTruot::ThanhTruot(
	DXTexture *pTexture,
	D3DXVECTOR2 position,
	D3DXVECTOR2 velocity)
	:DynamicObject(pTexture, position, NONE, velocity)
{
	this->_OType = EObjectName::THANHTRUOT_OBJECT;

	this->_castleTexture = pTexture;
	this->_velocity.y /= 2.0f;

	this->_width = _castleTexture->GetWidth();
	this->_height = _castleTexture->GetHeight();

	this->_color = D3DXCOLOR(1, 1, 1, 1);
}

void ThanhTruot::Draw(DXGame *pDXGame, Camera *pCamera)
{
	_texture = _castleTexture;

	BaseObject::Draw(pDXGame, pCamera, _color);
}

void ThanhTruot::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
}

void ThanhTruot::UpdateObjectState(GameTime *gameTime)
{
	this->UpdateMoving();
}

void ThanhTruot::UpdateMoving()
{
	_velocity.x += _temp.x * _deltaTime;

	if (_position.x <  300)
	{
		_position.x += 2;
	}

	if (_position.x > 300)
	{
		_position.x -= 2;
	}

	//_position.x += 2;
}


CollisionDirection ThanhTruot::CheckCollisions(BaseObject *obj)
{
	return Collision::CheckCollisions(this, obj);
}

void ThanhTruot::ResponseCollisions()
{

}