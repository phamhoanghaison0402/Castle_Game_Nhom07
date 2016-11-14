#include "GameInfo.h"


Score::Score(DXTexture *pNumTexture, D3DXVECTOR2 position)
	: BaseInfo(NULL, position)
{
	_score = 0;

	for (int i = 0; i < 5; i++)
	{
		numbers[i] = new Number(
			pNumTexture, 
			D3DXVECTOR2(this->_position.x + _width + i * pNumTexture->GetWidth() / 10, this->_position.y)
			);
	}
}

void Score::UpdateAnimation()
{
	int tmpScore, i;
	tmpScore = _score;

	i = 4; // chữ số bên phải
	int unit; // chữ số hàng đơn vị
	while (tmpScore > 0)
	{
		unit = tmpScore % 10;
		numbers[i]->SetValue(unit);
		
		tmpScore /= 10;
		i--;
	}
}

int Score::GetScore()
{
	return _score;
}

bool Score::SetScore(int score)
{
	if (score < 0 || score > 99999)
		return false;

	this->_score = score;
	this->UpdateAnimation();
	return true;
}

void Score::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	for (int i = 0; i < 5; i++)
	{
		numbers[i]->Draw(pDXGame, color);
	}
}



Life::Life(DXTexture *pTexture, DXTexture *pNumTexture, D3DXVECTOR2 position)
	: BaseInfo(pTexture, position)
{
	_life = 0;

	for (int i = 0; i < 2; i++)
	{
		numbers[i] = new Number(
			pNumTexture, 
			D3DXVECTOR2(this->_position.x + _width + i * pNumTexture->GetWidth() / 10, this->_position.y + _height / 2 - pNumTexture->GetHeight() / 2)
			);
	}
}

void Life::UpdateAnimation()
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

int Life::GetLife()
{
	return _life;
}

bool Life::SetLife(int score)
{
	if (score < 0 || score > 99)
		return false;

	this->_life = score;
	this->UpdateAnimation();
	return true;
}

void Life::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	BaseInfo::Draw(pDXGame, color); // icon
	for (int i = 0; i < 2; i++)
	{
		numbers[i]->Draw(pDXGame, color);
	}
}



World::World(DXTexture *pTexture, DXTexture *pNumTexture, D3DXVECTOR2 position)
	: BaseInfo(pTexture, position)
{
	_world = 1;

	for (int i = 0; i < 2; i++)
	{
		numbers[i] = new Number(
			pNumTexture, 
			D3DXVECTOR2(this->_position.x + _width + i * pNumTexture->GetWidth() / 10, this->_position.y + _height / 2 - pNumTexture->GetHeight() / 2)
			);
	}
}

void World::UpdateAnimation()
{
	int tmpScore, i;
	tmpScore = _world;

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

int World::GetWorld()
{
	return _world;
}

bool World::SetWorld(int score)
{
	if (score < 1 || score > 99)
		return false;

	this->_world = score;
	this->UpdateAnimation();
	return true;
}

void World::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	BaseInfo::Draw(pDXGame, color); // icon
	for (int i = 0; i < 2; i++)
	{
		numbers[i]->Draw(pDXGame, color);
	}
}



GameInfo::GameInfo(DXTexture *pMarioTexture, DXTexture *pWorldTexture, DXTexture *pNumTexture)
{
	// căn theo mario icon vì: mario icon có size lớn nhất
	_score = new Score(
		pNumTexture, 
		D3DXVECTOR2(0, 10 + pMarioTexture->GetHeight() / 2 - pNumTexture->GetHeight() / 2)
		);

	_world = new World(
		pWorldTexture, 
		pNumTexture, 
		D3DXVECTOR2(
			SCREEN_WIDTH / 2 - (pWorldTexture->GetWidth() + pNumTexture->GetWidth() / 10) / 2, 
			10 + pMarioTexture->GetHeight() / 2 - pWorldTexture->GetHeight() / 2
			)
		);

	_life = new Life(
		pMarioTexture, 
		pNumTexture, 
		D3DXVECTOR2(
			SCREEN_WIDTH - (pMarioTexture->GetWidth() + 2 * pNumTexture->GetWidth() / 10),
			10
			)
		);
}

void GameInfo::Draw(DXGame *pDXGame, D3DCOLOR color)
{
	//_score->Draw(pDXGame, color);
	//_world->Draw(pDXGame, color);
	//_life->Draw(pDXGame, color);
}

int GameInfo::GetScore()
{
	return _score->GetScore();
}

bool GameInfo::SetScore(int score)
{
	return _score->SetScore(score);
}

int GameInfo::GetWorld()
{
	return _world->GetWorld();
}

bool GameInfo::SetWorld(int world)
{
	return _world->SetWorld(world);
}

int GameInfo::GetLife()
{
	return _life->GetLife();
}

bool GameInfo::SetLife(int life)
{
	return _life->SetLife(life);
}

void GameInfo::LifeUp()
{
	_life->SetLife(_life->GetLife() + 1);
}

void GameInfo::LifeDown()
{
	_life->SetLife(_life->GetLife() - 1);
}

void GameInfo::AddScore(int score)
{
	_score->SetScore(_score->GetScore() + score);
}

void GameInfo::WorldUp()
{
	_world->SetWorld(_world->GetWorld() + 1);
}