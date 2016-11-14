#ifndef _NUMBER_H_
#define _NUMBER_H_


#include "BaseInfo.h"


class Number : public BaseInfo
{
	int _value;
public:
	Number(DXTexture *, D3DXVECTOR2);
	virtual bool SetValue(int x);
	virtual int GetValue();
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(0,0,0)); // Vẽ Object co dinh
};

#endif