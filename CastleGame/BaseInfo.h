#ifndef _BASEINFO_H_
#define _BASEINFO_H_

#include "BaseObject.h"


class BaseInfo : public BaseObject
{
public:
	BaseInfo(DXTexture *, D3DXVECTOR2);
	virtual void Update(GameTime *); // Update Object
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255)); // Vẽ Object co dinh
};

#endif