#include "StaticObject.h"


StaticObject::StaticObject(DXTexture *pTexture, D3DXVECTOR2 position)
	:BaseObject(pTexture, position)
{
}

void StaticObject::Update(GameTime *gameTime)
{
	//BaseObject::Update(gameTime);
}

void StaticObject::Draw(DXGame *pDXGame, Camera *pCamera)
{
	BaseObject::Draw(pDXGame, pCamera);
}