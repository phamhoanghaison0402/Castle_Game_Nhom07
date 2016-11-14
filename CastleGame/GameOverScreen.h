#ifndef _GAMEOVERSCREEN_H_
#define _GAMEOVERSCREEN_H_


#include "BaseInfo.h"


class GameOverScreen : public BaseInfo
{
public:
	GameOverScreen(DXTexture *);
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255)); // Vẽ Object co dinh
};

#endif