#include "PauseMenu.h"


PauseMenu::PauseMenu(DXTexture *pTexture, D3DXVECTOR2 position)
	: BaseInfo(pTexture, position)
{
	this->_width = this->_texture->GetWidth() / 2; // 2 nua
	
	_selection = PResume;
	_offX = 1;
	_offY = 0;
	_w = _width;
	_h = _height / 4;
	_posItem = _position;
}

void PauseMenu::GoNext()
{
	if (_selection < PQuit)
	{
		_selection = (PauseSelection)((int)_selection + 1);
	}
	else
	{
		_selection = PResume;
	}

	// update vị trí của item chọn
	_offY = (int)_selection;
	_posItem.y = _position.y + _h * _offY;
}

void PauseMenu::GoBack()
{
	if (_selection > PResume)
	{
		_selection = (PauseSelection)((int)_selection - 1);
	}
	else
	{
		_selection = PQuit;
	}

	// update vị trí của item chọn
	_offY = (int)_selection;
	_posItem.y = _position.y + _h * _offY;
}

PauseSelection PauseMenu::GetSelection()
{
	return _selection;
}

void PauseMenu::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	// xác định rect cắt frame animation
	_rItem.left = _offX * _w;
	_rItem.right = _rItem.left + _w;
	_rItem.top = _offY * _h;
	_rItem.bottom = _rItem.top + _h;
	
	BaseInfo::Draw(pDXGame, color);
	pDXGame->DrawTexture(_texture, &_posItem, &_rItem, color);
}