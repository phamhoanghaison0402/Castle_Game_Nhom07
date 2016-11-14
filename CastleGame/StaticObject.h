#ifndef _STATICOBJECT_H_
#define _STATICOBJECT_H_

#include "BaseObject.h"


class StaticObject : public BaseObject
{
public:
	StaticObject(DXTexture *, D3DXVECTOR2);
	virtual void Update(GameTime *); // Update
	virtual void Draw(DXGame *, Camera *); // Vẽ
};

#endif