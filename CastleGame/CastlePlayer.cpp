#include "CastlePlayer.h"


CastlePlayer::CastlePlayer(
	DXTexture *pTexture , 
	DXTexture *pNormalTexture, 
	DXTexture *pSuperTexture, 
	DXTexture *pBulletTexture, 
	D3DXVECTOR2 position, 
	CastleType type,
	D3DXVECTOR2 velocity, 
	D3DXVECTOR2 a)
	:DynamicObject(pTexture, position, NONE, velocity)
{
	this->_OType = EObjectName::MARIO_OBJECT;

	this->_pSmallTexture = pTexture;
	this->_pNormalTexture = pNormalTexture;
	this->_pSuperTexture = pSuperTexture;
	this->_pBulletTexture = pBulletTexture;

	if (type == CastleType::CASTLE_WALK)
	{
		this->_width = _pSmallTexture->GetWidth()/4;
		this->_height = _pSmallTexture->GetHeight()/2;
		this->_Type = CASTLE_WALK;
	}
	else if (type == CastleType::CASTLE_SIT)
	{
		this->_width = _pNormalTexture->GetWidth() / 3;
		this->_height = _pNormalTexture->GetHeight() / 2;
		this->_Type = CASTLE_SIT;
	}
	else
	{
		this->_width = _pSuperTexture->GetWidth() / 3;
		this->_height = _pSuperTexture->GetHeight() / 2;
		this->_Type = CASTLE_BULLET;
	}
	
	//this->_lastType = _Type;
	this->_EatMushroom = false;
	this->_EatFlower = false;
	this->_IsSmaller = false;
	this->_timeToGrownUp = 0.0f;

	this->_IsImmortality = false;
	this->_timeImr = 0.0f;
	this->_totalTimeImr = 0.0f;
	this->_nImr = 0;
	this->_color = D3DXCOLOR(1,1,1,1);

	this->_SMoveLeft = false;
	this->_SMoveRight = true;
	this->_SJump = false;
	this->_SFall = false;
	this->_SDie = false;
	this->_Run = false;
	this->_Sit = false;
	this->_isDead = false;

	this->_maxV = 1.0f * _velocity ;
	this->_a = a;
	this->_maxA = a;	
	if (a.y > 0)
	{
		_a.y *= -1;
		_maxA.y *= -1;
	}

	this->_velocity.y = 0;
	this->_velocity.x = 0;

	this->_moveX = 0.0f;
	this->_moveY = 0.0f;
	this->_flagCollisionX = 0;
	this->_flagCollisionY = 0;

	this->_nBullet = 0;
	this->_throwBullet = false;
	for (int i = 0; i < 3; i++)
	{
		_Bullet[i] = NULL;
	}
}

void CastlePlayer::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
	this->UpdateBullets(gameTime);
}


void CastlePlayer::UpdateBullets(GameTime *gameTime)
{
	for (int i = 0; i < 3; i++)
	{
		if (_Bullet[i] != NULL)
		{
			if (_Bullet[i]->_position.y < 0
				|| _Bullet[i]->_position.x > _position.x + SCREEN_WIDTH / 2
				|| _Bullet[i]->_position.x < _position.x - SCREEN_WIDTH / 2
				|| _Bullet[i]->_position.y < _position.y - SCREEN_HEIGHT / 2
				|| _Bullet[i]->_isDead == true)
			{
				_Bullet[i] = NULL;
				_nBullet -= 1;
			}
			else
			{
				_Bullet[i]->Update(gameTime);
			}
		}
	}
}

void CastlePlayer::DrawBullets(DXGame *pDXGame, Camera *pCamera)
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (_Bullet[i] != NULL && _Bullet[i]->_isDead == false)
		{
			_Bullet[i]->Draw(pDXGame, pCamera);
		}
	}
}

bool CastlePlayer::CheckBulletsCollision(BaseObject *obj)
{
	CollisionDirection dir = CollisionDirection::NONE_COL;
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (_Bullet[i] != NULL && _Bullet[i]->_isDead == false)
		{
			dir = _Bullet[i]->CheckCollisions(obj);
		}
	}

	return (dir != CollisionDirection::NONE_COL);
}

void CastlePlayer::Draw(DXGame *pDXGame, Camera *pCamera)
{
	if (_Type == CASTLE_WALK)
	{
		_texture = _pSmallTexture;
	}
	else if (_Type == CASTLE_SIT)
	{
		_texture = _pNormalTexture;
	}
	else if (_Type == CASTLE_BULLET)
	{
		_texture = _pSuperTexture;
	}
	
	BaseObject::Draw(pDXGame, pCamera, _color);
}

void CastlePlayer::UpdateBound()
{
	if (!_Sit)
	{
		DynamicObject::UpdateBound();
	}
	else
	{
		// cập nhật hình chữ nhật bao quanh đối tượng
		_rect.left = _position.x - _width / 2 + 1;
		_rect.right = _rect.left + _width - 2;
		_rect.top = _position.y - 1;
		_rect.bottom = _rect.top - _height / 2.0f + 2;
	}
}

void CastlePlayer::UpdateObjectState(GameTime *gameTime)
{
	if (_SDie)
	{
		_velocity.y += _a.y * _deltaTime; 
		_position.y += _velocity.y * _deltaTime;

		if (!_isDead)
		{
			if (_time > TIME_OF_MARIO_DIE)
			{
				_isDead = true;
			}
		}

		return;
	}

	if (_Sit)
		return;

	this->UpdateMoving();
}

void CastlePlayer::UpdateMoving()
{
	if (_SMoveLeft || _SMoveRight) 
	{
		if (_SMoveLeft)
		{
			if (_a.x > 0) 
			{
				_a.x *= -1; 
			}
		}
		else if (_SMoveRight)
		{
			if (_a.x < 0) 
			{
				_a.x *= -1;
			}
		}
		
		_velocity.x += _a.x * _deltaTime; 
		if (_velocity.x < -_maxV.x)
		{
			_velocity.x = -_maxV.x;
		}
		else if (_velocity.x > _maxV.x)
		{
			_velocity.x = _maxV.x;
		}
	}
	else // set về 0 nếu k di chuyển
	{
		if (_velocity.x * _a.x > 0) // chậm dần -> v*a < 0
		{
			_a.x *= -1;
		}

		if (abs(_velocity.x) > 0)
		{
			if (abs(_velocity.x) + _a.x * _deltaTime < 0) // khi v ~ 0 -> v = 0
			{
				_velocity.x = 0; 
			}
			else
			{
				if (_flagCollisionY != 3) // tranh bi troi khi thanh bar di chuyen
				{
					_velocity.x += _a.x * _deltaTime; 
				}
			}
		}
	}

	if (_SJump) 
	{
		if (_velocity.y <= 0) // khi v ~ 0 -> v = 0 -> đạt cực đại -> rơi xuống
		{
			_velocity.y = 0;
			_SJump = false;
			_SFall = true;
		}
		else
		{
			_velocity.y += _a.y * _deltaTime;
		}
	}
	else
	{
		if (_SFall)
		{
			_velocity.y += _a.y * _deltaTime; 
			if (_position.y < -_height / 2)
			{
				_SFall = false;
				_velocity.y = 0;
			}
		}
		else
		{
			if (_vel_Y == 0)
			{
				_velocity.y = 0;
			}
		}
	}

	_position.x += 1.1f * _velocity.x * _deltaTime/3 ;
	_position.y += _velocity.y * _deltaTime ;
}

void CastlePlayer::UpdateAnimation()
{
	if (_IsImmortality)
	{
		_timeImr += _deltaTime * 1000;
		_totalTimeImr += _deltaTime * 1000;
		if (_timeImr > TIME_OF_MARIO_TYPE_CHANGING)
		{
			_timeImr = 0.0f;
			_nImr += 1;
			if (_nImr % 2 == 0)
			{
				_color = D3DXCOLOR(0.6f, 0.5f, 0.5f, 1.0f);
			}
			else
			{
				_color = D3DXCOLOR(1, 1, 1, 1);
			}

			if (_totalTimeImr > MAX_TIME_OF_MARIO_IMMORTALITY)
			{
				_IsImmortality = false;
				_color = D3DXCOLOR(1, 1, 1, 1);
			}
		}
	}

	if (_SMoveLeft)
	{
		_offset_Y = 1;
	}
	else if (_SMoveRight)
	{
		_offset_Y = 0;
	}

	if (_SDie)
	{
		_offset_X = 4;
		return;
	}

	if (_Sit)
	{
		_Type = CASTLE_SIT;

		if (_Type == CASTLE_SIT)
		{
			_offset_X = 0;
		}

		/*if (_Type == SMALL_MARIO)
		{
		_offset_X = 3;
		}
		else
		{
		_offset_X = 4;
		}*/

		return;
	}
	else
	{
		_Type = CASTLE_WALK;
	}

	if (_SJump | _SFall) // Nếu nhảy/ rớt -> set vận tốc nhảy, rơi
	{
		if (_Type == CASTLE_WALK)
		{
			_offset_X = 2;
		}
		else // Mario lớn
		{
			if (_SJump)
			{
				_offset_X = 3;
			}
			else
			{
				_offset_X = 2;
			}
		}

		return;
	}

	if (_SMoveLeft || _SMoveRight)
	{
		// mario trượt khi di chuyển và quay lại gấp
		if (_SMoveRight && _velocity.x < 0)
		{
			_offset_X = 1;
			return;
		}
		else if (_SMoveLeft && _velocity.x > 0)
		{
			_offset_X = 1;
			return;

		}

		if (!_Run) // Khi đi
		{
			if (_time >= 200)
			{
				_time = 0;
				_offset_X++;
				if (_offset_X > 1)
				{
					_offset_X = 0;
				}
			}
		}
		else // khi chạy
		{
			if (_time >= 8)
			{
				_time = 0;
				_offset_X++;
				if (_offset_X > 1)
				{
					_offset_X = 0;
				}
			}
		}

		return;
	}

	if (_Roi)
	{
		_Type = CASTLE_BULLET;

		if (_Type == CASTLE_BULLET)
		{
			//_offset_X = 0;
			if (_time >= 500)
			{
				_time = 0;
				_offset_X++;
				if (_offset_X > 2)
				{
					_offset_X = 0;
				}
			}
		}
	}
	else
	{
		_Type = CASTLE_WALK;
	}

	if (_throwBullet)
	{
		_offset_X = 1;
		if (_time > MAX_TIME_OF_MARIO_THROW_BULLETS)
		{
			_time = 0;
			_throwBullet = false;
		}
		return;
	}

	// trạng thái đứng yên
	_offset_X = 0;
}

void CastlePlayer::ThrowBullet(list<BaseObject *> &l)
{
	
	if (_nBullet < 3)
	{
		for (int i = 0; i < 3; i++)
		{
			if (_Bullet[i] == NULL)
			{
				D3DXVECTOR2 pos;
				D3DXVECTOR2 vel;
				if (_offset_Y == 0) // quay hướng phải
				{
					pos = D3DXVECTOR2(_position.x + _width / 2.0f, _position.y + _height / 4.0f);
					vel = D3DXVECTOR2(_velocity.x + 500, 800);
				}
				else
				{
					pos = D3DXVECTOR2(_position.x - _width / 2.0f, _position.y + _height / 4.0f);
					vel = D3DXVECTOR2(_velocity.x + -500, 800);
				}

				_Bullet[i] = new Boomerang(_pBulletTexture, pos, vel);
				l.push_back(_Bullet[i]);
				_nBullet += 1;
				_throwBullet = true;
				_time = 0;
				return;
			}
		}
	}
}

Box CastlePlayer::GetBoardBox()
{
	if (_vel_Y != 0)
	{
		if (_vel_Y < 0)
		{
			return ConvertRectToBoardBox(
				_rect,
				_velocity.x * _deltaTime,
				(_velocity.y - 200) * _deltaTime);
		}
		else
		{
			return ConvertRectToBoardBox(
				_rect,
				_velocity.x * _deltaTime,
				(-200) * _deltaTime);
		}
	}
	else
	{
		return DynamicObject::GetBoardBox();
	}
}

Box CastlePlayer::GetBoardBox(D3DXVECTOR2 v)
{
	return DynamicObject::GetBoardBox(v);
}

void CastlePlayer::TransferPosition(float x, float y)
{
	_position.x += x;
	_position.y += y;

	_rect.left += x;
	_rect.right += x;
	_rect.top += y;
	_rect.bottom += y;
}


void CastlePlayer::MoveLeft()
{
	_SMoveLeft = true;
	_SMoveRight = false;
}

void CastlePlayer::MoveRight()
{
	_SMoveRight = true;
	_SMoveLeft = false;
}

void CastlePlayer::NoneMove()
{
	_SMoveLeft = false;
	_SMoveRight = false;
}

void CastlePlayer::Jump()
{
	if (_SFall)
		return;

	_SJump = true;
	//_flagJump = true;
	_velocity.y = _maxV.y;
}

void CastlePlayer::Jump(float vy)
{
	if (_SFall)
		return;

	if (vy < 0)
	{
		vy *= -1;
	}

	_SJump = true;
	//_flagJump = true;
	_velocity.y = vy;
}

void CastlePlayer::Run()
{
	_Run = true;

	_maxV.x = 800;
	_maxV.y = 1400;
	
	_maxA.x = _a.x = 800;
	_maxA.y = _a.y = -4000;
	
}

void CastlePlayer::NoneRun()
{
	_Run = false;

	_maxV.x = 500;
	_maxV.y = 1100;		
	_maxA.x = _a.x = 900;
	_maxA.y = _a.y = -3000;
}

void CastlePlayer::Sit()
{
	if (_SJump || _SFall)
		return;

	_Sit = true;
	_velocity.x = 0;
	_velocity.y = 0;
}

void CastlePlayer::NoneSit()
{
	_Sit = false;
}


void CastlePlayer::PhongRoi()
{
	_Roi = true;
}

void CastlePlayer::NonePhongRoi()
{
	_Roi = false;
}


void CastlePlayer::ResponseCollisionsWithEnemy()
{
	if (_EatMushroom || _EatFlower || _IsSmaller || _IsImmortality)
	{
		return;
	}
}

void CastlePlayer::Immortality()
{
	_IsImmortality = true;
	_timeImr = 0.0f;
	_nImr = 0;
	_totalTimeImr = 0.0f;
}

void CastlePlayer::BeginToCheckCollisions()
{
	if (_SDie)
		return;

	this->_SFall = true;
	_a = _maxA;
	Collision::BeginToCheckCollisions();
}

void CastlePlayer::TopCol(BaseObject *obj)
{
	//_velocity.y = 0;
	/*if (obj->GetType() == EObjectName::GODOWN_BAR_OBJECT
		|| obj->GetType() == EObjectName::GOUP_BAR_OBJECT)
	{
		_vel_Y = ((DynamicObject *)obj)->_velocity.y;
		_flagCollisionY = 2;
	}
	else if (obj->GetType() == EObjectName::HORIZONTAL_BAR_OBJECT)
	{
		_vel_X = ((DynamicObject *)obj)->_velocity.x;
		_flagCollisionY = 3;
	}
	
	else
	{*/
		Collision::TopCol(obj);
	/*}*/
	_SFall = false;
}

void CastlePlayer::BottomCol(BaseObject *obj)
{
	/*if (obj->GetType() == EObjectName::GODOWN_BAR_OBJECT)
	{
		_vel_Y = ((DynamicObject *)obj)->_velocity.y;
		_flagCollisionY = -2;
	}
	else
	{*/
		Collision::BottomCol(obj);
	/*}*/
	_SJump = false;
	_SFall = true;
}

void CastlePlayer::LeftCol(BaseObject *obj)
{
	_SMoveRight = false;
	Collision::LeftCol(obj);
}

void CastlePlayer::RightCol(BaseObject *obj)
{
	/*if (obj->GetType() == EObjectName::COIN_OBJECT)
	{*/
		return;
	/*}*/

	_SMoveLeft = false;
	Collision::RightCol(obj);
}

CollisionDirection CastlePlayer::CheckCollisions(BaseObject *obj)
{
	if (_SDie)
		return CollisionDirection::NONE_COL;

	return Collision::CheckCollisions(this, obj);
}

void CastlePlayer::ResponseCollisions()
{
	if (_SDie)
		return;

	Collision::TransferPosition(_position);

	if (_flagCollisionX != 0)
	{
		_velocity.x = 0;
	}
	else
	{
	}
	
	if (_flagCollisionY != 0)
	{
		if (_flagCollisionY == 1)
		{
			_velocity.y = 0;
			_a.y = _maxA.y;
			_vel_Y = 0;
			_vel_X = 0;
		}
		else if (_flagCollisionY == 2)
		{
			if (_SJump == false)
			{
				_velocity.y = _vel_Y;
				_a.y = 0;
			}
			else
			{
				// v mac dinh.
			}

			return;
		}
		else if (_flagCollisionY == 3)
		{
			if (!(_SMoveLeft == true || _SMoveRight == true))
			{
				_velocity.x = _vel_X;
				_a.x = 0;
			}
		}
		else if (_flagCollisionY == -2)
		{
			_velocity.y = _vel_Y;
		}
		else 
		{
			_velocity.y = 0;
		}
	}
	else
	{
	}
}

void CastlePlayer::ResponseAsNoCollision(BaseObject *obj, CollisionDirection dir)
{
	if (_SDie)
		return;

	if (dir == CollisionDirection::TOP_COL
		|| dir == CollisionDirection::BOTTOM_COL)
	{
		this->_SFall = true;
		_flagCollisionY = 0;
		_moveY = 0.0f;
	}
	else if (dir == CollisionDirection::LEFT_COL
		|| dir == CollisionDirection::RIGHT_COL)
	{
		_moveX = 0.0f;
		_flagCollisionX = 0;
	}
}