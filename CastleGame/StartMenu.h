﻿#ifndef _STARTMENU_H_
#define _STARTMENU_H_


#include "BaseInfo.h"


enum StartSelection
{
	SStart = 0,
	SQuit
};

class StartMenu : public BaseInfo
{
private:
	StartSelection _selection;
	int _w, _h; // kich thuoc doi tuong duoc chon
	int _offX, _offY; // offset cua selectedItem
	RECT _rItem; // HCN source Item
	D3DXVECTOR2 _posItem; // vị trí của item chọn
public:
	StartMenu(DXTexture *, D3DXVECTOR2);
	virtual void GoNext(); // xuống
	virtual void GoBack(); // lên
	virtual StartSelection GetSelection();
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,220,255)); // Vẽ Object co dinh
};

#endif