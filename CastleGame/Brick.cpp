#include "Brick.h"


Brick::Brick(DXTexture *pTexture, DXTexture *pExploredTexture, D3DXVECTOR2 position, DXTexture *pCoinTexture, bool hasCoin)
	:DynamicObject(pTexture, position, JUMP)
{
	this->_width = pTexture->GetWidth() / 2;
	this->_height = pTexture->GetHeight();

	this->_origin_Y = _position.y;
	this->_time = 0;
	this->_isMovedUp = false;
	this->_isCollision = false;
	this->_isExplored = false;
	this->_isDisappear = false;
	this->_isColFirst = false;
}

void Brick::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
}

void Brick::Draw(DXGame *pDXGame, Camera *pCamera)
{

	if (!_isExplored)
	{
		DynamicObject::Draw(pDXGame, pCamera);
	}
	else
	{
		if (!_isDisappear)
		{
			for (int i = 0; i < 4; i++)
			{
				_pFraments[i]->Draw(pDXGame, pCamera);
			}
		}
	}
}

void Brick::UpdateObjectState(GameTime *gameTime)
{
	DynamicObject::UpdateObjectState(gameTime);
}

void Brick::UpdateAnimation()
{
	if (!_hasCoin)
	{
		_offset_X = 0;
	}
	else
	{
		if (!_isExplored)
		{
			_offset_X = 0;
		}
		else
		{
			_offset_X = 1;
		}
	}

	DynamicObject::UpdateAnimation();
}

Brick::~Brick()
{
	if (_coin != NULL)
	{
		delete _coin;
		_coin = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		if (_pFraments[i] != NULL)
		{
			delete _pFraments[i];
			_pFraments[i] = NULL;
		}
	}
}

void Brick::HasCollision()
{
		_isMovedUp = true;
	
}