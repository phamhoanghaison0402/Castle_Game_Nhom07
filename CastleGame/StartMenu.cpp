#include "StartMenu.h"


StartMenu::StartMenu(DXTexture *pTexture, D3DXVECTOR2 position)
	: BaseInfo(pTexture, position)
{
	this->_width = this->_texture->GetWidth() / 2; // 2 nua
	
	_selection = SStart;
	_offX = 1;
	_offY = 0;
	_w = _width;
	_h = _height / 2;
	_posItem = _position ;
}

void StartMenu::GoNext()
{
	if (_selection < SQuit)
	{
		_selection = (StartSelection)((int)_selection + 1);
	}
	else
	{
		_selection = SStart;
	}

	// update vị trí của item chọn
	_offY = (int)_selection;
	_posItem.y = _position.y + _h * _offY;
}

void StartMenu::GoBack()
{
	if (_selection > SStart)
	{
		_selection = (StartSelection)((int)_selection - 1);
	}
	else
	{
		_selection = SQuit;
	}

	// update vị trí của item chọn
	_offY = (int)_selection;
	_posItem.y = _position.y + _h * _offY;
}

StartSelection StartMenu::GetSelection()
{
	return _selection;
}

void StartMenu::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	// xác định rect cắt frame animation
	_rItem.left = _offX * _w ;
	_rItem.right = _rItem.left + _w;
	_rItem.top = _offY * _h ;
	_rItem.bottom = _rItem.top + _h;
	
	BaseInfo::Draw(pDXGame, color);
	pDXGame->DrawTexture(_texture, &_posItem, &_rItem, color);
}