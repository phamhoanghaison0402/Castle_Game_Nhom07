#include "Number.h"

Number::Number(DXTexture *pTexture, D3DXVECTOR2 position)
	: BaseInfo(pTexture, position)
{
	this->_width = this->_texture->GetWidth() / 10;
	this->_height = this->_texture->GetHeight();

	this->_value = 0;
}

bool Number::SetValue(int x)
{
	if (x < 0 || x > 9)
		return false;

	_value = x;
	this->_offset_X = _value;

	return true;
}

int Number::GetValue()
{
	return _value;
}

void Number::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	BaseInfo::Draw(pDXGame, color);
}