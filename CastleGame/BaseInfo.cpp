#include "BaseInfo.h"


BaseInfo::BaseInfo(DXTexture *pTexture, D3DXVECTOR2 position)
	: BaseObject(pTexture, position)
{

}

void BaseInfo::Update(GameTime *)
{

}

void BaseInfo::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	// xác định rect cắt frame animation
	_rectSource.left = _offset_X * _width;
	_rectSource.right = _rectSource.left + _width;
	_rectSource.top = _offset_Y * _height;
	_rectSource.bottom = _rectSource.top + _height;

	pDXGame->DrawTexture(_texture, &_position, &_rectSource, color);
}