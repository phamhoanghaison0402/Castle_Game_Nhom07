#include"Boomerang.h"


Boomerang::Boomerang(DXTexture *pTexture, D3DXVECTOR2 position, D3DXVECTOR2 velocity, D3DXVECTOR2 a)
	: DynamicObject(pTexture, position, NONE, velocity)
{
	this->_OType = EObjectName::BULLET_OBJECT;

	this->_width = _texture->GetWidth() / 3;
	this->_height = _texture->GetHeight();

	_a = a;
	if (_a.y > 0)
	{
		_a.y *= -1;
	}
	_maxV = velocity;
	if (_maxV.y < 0)
	{
		_maxV.y *= -1;
	}
	_velocity.y = 0;
}

void Boomerang::Update(GameTime *gameTime)
{
	if (!_isDead)
	{
		DynamicObject::Update(gameTime);
	}
}

void Boomerang::Draw(DXGame *pDXGame, Camera *pCamera)
{
	if (!_isDead)
	{
		DynamicObject::Draw(pDXGame, pCamera);
	}
}

void Boomerang::UpdateObjectState(GameTime *gameTime)
{
	float pos = _position.x;

	if (!_isDead) // sống
	{
		_position.x += _velocity.x * _deltaTime;
		_velocity.x += _a.x * _deltaTime;

		if (_position.x > SCREEN_WIDTH)
		{		
			_position.x -= _velocity.x * _deltaTime;
			_velocity.x += _a.x * _deltaTime;

		}

		return;
	}
}

void Boomerang::UpdateAnimation()
{
	if (!_isDead)
	{
		if (_time > 50)
		{
			_time = 0;
			_offset_X += 1;
			if (_offset_X > 2)
			{
				_offset_X = 0;
			}
		}
	}
}


void Boomerang::BeginToCheckCollisions()
{
	Collision::BeginToCheckCollisions();
}

void Boomerang::TopCol(BaseObject *obj)
{
	if (obj->GetType() == EObjectName::BOSS_1_OBJECT)
	{
		_isDead = true;
	}
	Collision::TopCol(obj);
}

void Boomerang::BottomCol(BaseObject *obj)
{
	Collision::BottomCol(obj);
}

void Boomerang::LeftCol(BaseObject *obj)
{
	Collision::LeftCol(obj);
}

void Boomerang::RightCol(BaseObject *obj)
{
	Collision::RightCol(obj);
}

CollisionDirection Boomerang::CheckCollisions(BaseObject *obj)
{
	return Collision::CheckCollisions(this, obj);
}

void Boomerang::ResponseCollisions()
{
	if (_isDead)
		return;

	Collision::TransferPosition(_position);

	if (_flagCollisionY == 1)
	{
		_velocity.y = _maxV.y;
	}
	else if (_flagCollisionY == -1)
	{
		_velocity.y = 0;
	}

	if (_flagCollisionX != 0 && _flagCollisionY == 0)
	{
		_isDead = true;
	}
}