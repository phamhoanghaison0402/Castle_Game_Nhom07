#include "CanhCua.h"


CanhCua::CanhCua(
	DXTexture *pTexture,
	D3DXVECTOR2 position)
	:DynamicObject(pTexture, position, NONE)
{
	this->_OType = EObjectName::CANHCUA_OBJECT;

	this->_canhcuaTexture = pTexture;

	this->_width = _canhcuaTexture->GetWidth();
	this->_height = _canhcuaTexture->GetHeight();

	this->_color = D3DXCOLOR(1, 1, 1, 1);
}

void CanhCua::Draw(DXGame *pDXGame, Camera *pCamera)
{
	_texture = _canhcuaTexture;

	BaseObject::Draw(pDXGame, pCamera, _color);
}

void CanhCua::Update(GameTime *gameTime)
{
	DynamicObject::Update(gameTime);
}

void CanhCua::UpdateBound(){

	_rect.left = _position.x - _width / 2 + 1;
	_rect.right = _rect.left + _width - 2;
	_rect.top = _position.y - 1;
	_rect.bottom = _rect.top - _height / 2.0f + 2;
}


CollisionDirection CanhCua::CheckCollisions(BaseObject *obj)
{
	return Collision::CheckCollisions(this, obj);
}

void CanhCua::ResponseCollisions()
{

}