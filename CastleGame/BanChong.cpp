#include "BanChong.h"


BanChong::BanChong(DXTexture *pTexture, D3DXVECTOR2 position, Direction direction, D3DXVECTOR2 velocity)
	: Enemy(pTexture, position, direction, velocity)
{
	this->_width = _texture->GetWidth();
	this->_height = _texture->GetHeight();

	this->_angle = 0.0f;
	this->_origin_X = _position.x;
	this->_origin_Y = _position.y;
	this->_distance = 0;

	this->_OType = EObjectName::BANCHONG_OBJECT;
	this->_velocity.y /= 2.0f;


	this->_isDisappear = false;
//	this->_isCollisionWithCastle = false;
	this->_isCollisionWithBullet = false;
}

void BanChong::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
}

void BanChong::Draw(DXGame *pDXGame, Camera *pCamera)
{
	LivingObject::Draw(pDXGame, pCamera);
}

void BanChong::UpdateObjectState(GameTime *gameTime)
{
	DynamicObject::UpdateObjectState(gameTime);

	if (!_isDead)
	{
		_position.y -= _velocity.y * _deltaTime; // cập nhật X
		if (_position.y < _origin_Y - 300)
		{
			_direction = LEFT;
		}
		else if (_position.y > _origin_Y + 300)
		{
			_direction = RIGHT;
		}
	}
	else if (!_isDisappear)
	{
		_position.x += _velocity.x * _deltaTime;
		if (_position.x > SCREEN_HEIGHT)
		{
			_isDisappear = true;
		}
	}
}