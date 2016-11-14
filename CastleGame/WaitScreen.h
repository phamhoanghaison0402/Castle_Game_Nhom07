#ifndef _WAITSCREEN_H_
#define _WAITSCREEN_H_


#include "BaseInfo.h"
#include "Number.h"


class WaitScreen : public BaseInfo
{
private:
	int _life;
	Number *numbers[2];
public:
	WaitScreen(DXTexture *, DXTexture *);
	virtual void UpdateAnimation(); // Update Object
	virtual int GetLife();
	virtual bool SetLife(int);
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255)); // Vẽ Object co dinh
};

#endif