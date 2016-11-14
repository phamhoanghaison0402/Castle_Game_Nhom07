#include "Enemy.h"


Enemy::Enemy(DXTexture *pTexture, D3DXVECTOR2 position, Direction direction, D3DXVECTOR2 velocity)
	: LivingObject(pTexture, position, direction, velocity)
{
	this->_OType = EObjectName::BOSS_1_OBJECT;

	this->_width = _texture->GetWidth() / 4;
	this->_height = _texture->GetHeight();

	this->_isDisappear = false;
	this->_isCollisionWithMario = false;
	this->_isCollisionWithBullet = false;

	this->_SFreeFall = true;
	this->_maxV = _velocity;
	if (_maxV.y > 0)
	{
		_maxV.y *= -1;
	}
}

void Enemy::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
}

void Enemy::Draw(DXGame *pDXGame, Camera *pCamera)
{
	if (!_isDisappear)
	{
		DynamicObject::Draw(pDXGame, pCamera);
	}
}

void Enemy::UpdateObjectState(GameTime *gameTime)
{
	DynamicObject::UpdateObjectState(gameTime);

	if (!_isDead) // sống
	{
		_position.x += _velocity.x * _deltaTime;
		_position.y += _velocity.y * _deltaTime;
		return;
	}
	
	if (!_isDisappear) // chết nhưng chưa biến mất
	{
		if (_isCollisionWithMario)
		{
			if (_time > TIME_DISAPPEAR_OF_ENEMY)
			{
				_isDisappear = true;
			}
		}
		else
		{
			if (_time > 100)
			{
				_direction = FALL;
			}
			_position.y += _velocity.y * _deltaTime;
			if (_position.y < -_height)
			{
				_isDisappear = true;
			}
		}
	}
}

void Enemy::UpdateAnimation()
{
	if (!_isDead) // Sống
	{
		if (_time >= 400)
		{
			_time = 0;
			_offset_X++;
			if (_offset_X > 1)
			{
				_offset_X = 0;
			}
		}

		return;
	}

	if (_isCollisionWithMario) // Va chạm với Mario (bị Mario dậm)
	{
		_offset_X = 3;
		return;
	}

	if (_isCollisionWithBullet)
	{
		_offset_X = 2;
		return;
	}
}


void Enemy::BeginToCheckCollisions()
{
	_SFreeFall = true;
	Collision::BeginToCheckCollisions();
}

void Enemy::TopCol(BaseObject *obj)
{
	Collision::TopCol(obj);
}

void Enemy::BottomCol(BaseObject *obj)
{
	Collision::BottomCol(obj);
}

void Enemy::LeftCol(BaseObject *obj)
{
	Collision::LeftCol(obj);
}

void Enemy::RightCol(BaseObject *obj)
{
	Collision::RightCol(obj);
}

CollisionDirection Enemy::CheckCollisions(BaseObject *obj)
{
	return Collision::CheckCollisions(this, obj);
}

void Enemy::ResponseCollisions()
{
	if (_isDead)
		return;

	Collision::TransferPosition(_position);

	if (_flagCollisionX == -1)
	{
		_direction = LEFT;
	}
	else if (_flagCollisionX == 1)
	{
		_direction = RIGHT;
	}

	if (_flagCollisionY == 1)
	{
		_SFreeFall = false;
	}
	else if (_flagCollisionY == -1)
	{
		_direction = FALL;
	}


	if (_SFreeFall == false)
	{
		_velocity.y = 0;
	}
	else
	{
		_velocity.y = _maxV.y;
		_direction = FALL;
	}

	if (_velocity.y != 0)
	{
		if (_velocity.x > 0)
		{
			_velocity.x = 100;
			_direction = RIGHT;
		}
		else
		{
			_velocity.x = -100;
			_direction = LEFT;
		}
	}
	else
	{
		_velocity.x = _maxV.x;
	}
}


void Enemy::CollisionWithMario()
{
	if (_isCollisionWithMario == false)
	{
		this->_isCollisionWithMario = true;
		_direction = NONE;
		_time = 0;
		_isDead = true;
	}
}

void Enemy::CollisionWithBullet()
{
	if (_isCollisionWithBullet == false)
	{
		this->_isCollisionWithBullet = true;
		_direction = JUMP;
		_velocity.y = _maxV.y;
		_isDead = true;
		_time = 0;
	}
}

