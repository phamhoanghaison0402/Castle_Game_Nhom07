﻿#include "Doi.h"


Doi::Doi(DXTexture *pTexture, D3DXVECTOR2 position, Direction direction, D3DXVECTOR2 velocity)
	: Enemy(pTexture, position, direction, velocity)
{
	this->_width = _texture->GetWidth() / 4;
	this->_height = _texture->GetHeight() / 2;

	this->_angle = 0.0f;
	this->_origin_X = _position.x;
	this->_origin_Y = _position.y;
	this->_distance = 0;

	this->_OType = EObjectName::DOI_OBJECT;
	this->_velocity.y /= 2.0f;


	this->_isDisappear = false;
//	this->_isCollisionWithCastle = false;
	this->_isCollisionWithBullet = false;
}

void Doi::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
}

void Doi::Draw(DXGame *pDXGame, Camera *pCamera)
{
	LivingObject::Draw(pDXGame, pCamera);
}

void Doi::UpdateObjectState(GameTime *gameTime)
{
	DynamicObject::UpdateObjectState(gameTime);

	if (!_isDead)
	{
		_position.x += _velocity.x * _deltaTime; // cập nhật X
		if (_position.x < _origin_X - 300)
		{
			_direction = RIGHT;
		}
		else if (_position.x > _origin_X + 300)
		{
			_direction = LEFT;
		}

		// cập nhật Y
		_angle += _velocity.y * _deltaTime / 120.0f;
		if (_angle >= 2 * PI_NUMBER)
		{
			_angle = 0.0f;
		}
		// tạo đường zích zắc
		_position.y = _origin_Y + sin(_angle) * 50;
	}
	else if (!_isDisappear)
	{
		_position.y += _velocity.y * _deltaTime;
		if (_position.y > SCREEN_HEIGHT)
		{
			_isDisappear = true;
		}
	}

}

void Doi::UpdateAnimation()
{
	if (!_isDead)
	{
		if (!_isCollisionWithBullet)
		{
			if (_time >= 100) // chỉ số càng thấp, tạo animation càng nhanh
			{
				_time = 0;
				_offset_X++;
				if (_offset_X > 1)
				{
					_offset_X = 0;
				}
			}
		}
	}
}