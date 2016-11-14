#include "DynamicObject.h"

DynamicObject::DynamicObject(DXTexture *pTexture, D3DXVECTOR2 position, Direction direction, D3DXVECTOR2 velocity)
	:BaseObject(pTexture, position)
{
	this->_direction = direction;
	this->_velocity = velocity;
	this->_time = 0;
	this->_deltaTime = 0.0f;
	this->_isDead = false;
}

void DynamicObject::Update(GameTime *gameTime)
{
	_time += gameTime->GetElapsedTimePerFrameMiliSeconds();
	_deltaTime = gameTime->GetElapsedTimePerFrameSeconds();

	// Cập nhật trạng thái
	this->UpdateObjectState(gameTime);
	// Cập nhật frame animation
	this->UpdateAnimation();

	BaseObject::Update(gameTime);
}

void DynamicObject::Draw(DXGame *pDXGame, Camera *pCamera)
{
	BaseObject::Draw(pDXGame, pCamera);
}

void DynamicObject::UpdateBound()
{
	BaseObject::UpdateBound();
}

void DynamicObject::UpdateObjectState(GameTime *gameTime)
{
	if (_direction == NONE)
	{
		_velocity.x = 0;
		_velocity.y = 0;
		return;
	}

	if (_direction == LEFT)
	{
		if (_velocity.x > 0) 
		{
			_velocity.x *= -1;
		}
	}
	else if (_direction == RIGHT)
	{
		if (_velocity.x < 0)
		{
			_velocity.x *= -1;
		}
	}

	if (_direction == JUMP)
	{
		if (_velocity.y < 0)
		{
			_velocity.y *= -1;
		}
	}
	else if (_direction == FALL)
	{
		if (_velocity.y > 0)
		{
			_velocity.y *= -1;
		}
	}
}

void DynamicObject::UpdateAnimation()
{
	// Empty
}


bool DynamicObject::IsDead()
{
	return _isDead;
}


RECT DynamicObject::GetNodeBound()
{
	RECT r;
	r.left = _rect.left - 100;
	r.right = _rect.right + 100;
	r.top = _rect.top + 100;
	r.bottom = _rect.bottom - 100;

	return r;
}

Box DynamicObject::GetNonStaticObjectBox(D3DXVECTOR2 v)
{
	return ConvertRectToBox(
		_rect,
		(_velocity.x - v.x) * _deltaTime,
		(_velocity.y - v.y) * _deltaTime);
}

Box DynamicObject::GetBoardBox()
{
	if (_velocity.y != 0)
	{
		return ConvertRectToBoardBox(
			_rect,
			_velocity.x * _deltaTime,
			_velocity.y * _deltaTime);
	}
	else // đảm bảo khi vy = 0, vẫn xét 1 box mới để kiểm tra sự rơi tự do 1 cách an toàn hơn
	{
		return ConvertRectToBoardBox(
			_rect,
			_velocity.x * _deltaTime,
			-300 * _deltaTime);
	}
}

Box DynamicObject::GetBoardBox(D3DXVECTOR2 v)
{
	return ConvertRectToBoardBox(
		_rect,
		v.x * _deltaTime,
		v.y * _deltaTime);
}