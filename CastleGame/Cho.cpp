#include "Cho.h"


Cho::Cho(DXTexture *pTexture, D3DXVECTOR2 position, Direction direction, D3DXVECTOR2 velocity)
	: Enemy(pTexture, position, direction, velocity)
{
	this->_width = _texture->GetWidth();
	this->_height = _texture->GetHeight();

	this->_angle = 0.0f;
	this->_origin_X = _position.x;
	this->_origin_Y = _position.y;
	this->_distance = 0;

	this->_OType = EObjectName::MA_OBJECT;
	this->_velocity.y /= 2.0f;


	this->_isDisappear = false;
//	this->_isCollisionWithCastle = false;
	this->_isCollisionWithBullet = false;
}

void Cho::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
}

void Cho::Draw(DXGame *pDXGame, Camera *pCamera)
{
	LivingObject::Draw(pDXGame, pCamera);
}

void Cho::UpdateObjectState(GameTime *gameTime)
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
//
//void Ma::UpdateAnimation()
//{
//	if (!_isDead)
//	{
//		if (!_isCollisionWithCastle && !_isCollisionWithBullet)
//		{
//			if (_time >= 50) // chỉ số càng thấp, tạo animation càng nhanh
//			{
//				_time = 0;
//				_offset_X++;
//				if (_offset_X > 1)
//				{
//					_offset_X = 0;
//				}
//			}
//		}
//	}
//}