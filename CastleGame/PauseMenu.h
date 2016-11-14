#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_H_


#include "BaseInfo.h"

enum PauseSelection
{
	PResume = 0,
	PLoad,
	PSave,
	PQuit
};

class PauseMenu : public BaseInfo
{
private:
	PauseSelection _selection;
	int _w, _h; // kich thuoc doi tuong duoc chon
	int _offX, _offY; // offset cua selectedItem
	RECT _rItem; // HCN source Item
	D3DXVECTOR2 _posItem; // vị trí của item chọn
public:
	PauseMenu(DXTexture *, D3DXVECTOR2);
	virtual void GoNext(); // xuống
	virtual void GoBack(); // lên
	virtual PauseSelection GetSelection();
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255)); // Vẽ Object co dinh
};

#endif