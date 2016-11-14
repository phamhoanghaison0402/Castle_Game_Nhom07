#include "NgonNen.h"


NgonNen::NgonNen(
	DXTexture *pTexture,
	D3DXVECTOR2 position)
	:DynamicObject(pTexture, position, NONE)
{
	this->_OType = EObjectName::NGONNEN_OBJECT;

	this->_castleTexture = pTexture;

	this->_width = _castleTexture->GetWidth() / 2;
	this->_height = _castleTexture->GetHeight();

	this->_color = D3DXCOLOR(1, 1, 1, 1);
}

void NgonNen::Draw(DXGame *pDXGame, Camera *pCamera)
{
	_texture = _castleTexture;

	BaseObject::Draw(pDXGame, pCamera, _color);
}

void NgonNen::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
}

void NgonNen::UpdateAnimation()
{
	if (!_isDead)
	{
		if (_time >= 150) // chỉ số càng thấp, tạo animation càng nhanh
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


CollisionDirection NgonNen::CheckCollisions(BaseObject *obj)
{
	return Collision::CheckCollisions(this, obj);
}

void NgonNen::ResponseCollisions()
{

}