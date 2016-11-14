#include "GameOverScreen.h"


GameOverScreen::GameOverScreen(DXTexture *pTexture)
	: BaseInfo(pTexture, D3DXVECTOR2(0,0))
{

}

void GameOverScreen::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	BaseInfo::Draw(pDXGame, color);
}