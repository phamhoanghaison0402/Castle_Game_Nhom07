#include "WaitScreen.h"


WaitScreen::WaitScreen(DXTexture *pTexture, DXTexture *pNumTexture)
	: BaseInfo(pTexture, D3DXVECTOR2(0,0))
{
	_life = 0;

	for (int i = 0; i < 2; i++)
	{
		numbers[i] = new Number(
			pNumTexture, 
			D3DXVECTOR2(
					SCREEN_WIDTH / 2 + pNumTexture->GetWidth() / 10 / 2 + i * pNumTexture->GetWidth() / 10, 
					SCREEN_HEIGHT / 2 - pNumTexture->GetHeight() / 2
				)
			);
	}
}

void WaitScreen::UpdateAnimation()
{
	int tmpScore, i;
	tmpScore = _life;

	i = 1; // chữ số bên phải
	int unit; // chữ số hàng đơn vị
	while (tmpScore > 0)
	{
		unit = tmpScore % 10;
		numbers[i]->SetValue(unit);
		
		tmpScore /= 10;
		i--;
	}
}

int WaitScreen::GetLife()
{
	return _life;
}

bool WaitScreen::SetLife(int score)
{
	if (score < 0 || score > 99)
		return false;

	this->_life = score;
	this->UpdateAnimation();
	return true;
}

void WaitScreen::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	BaseInfo::Draw(pDXGame); // background
	for (int i = 0; i < 2; i++)
	{
		numbers[i]->Draw(pDXGame, color);
	}
}