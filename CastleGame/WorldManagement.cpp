#include "WorldManagement.h"
#include "GameWorld.h"


WorldManagement WorldManagement::_instance = WorldManagement();

void WorldManagement::Init()
{
	_isFinishWorld = false;
}

void WorldManagement::Cleanup()
{
	while (!_gameWorlds.empty())
	{
		_gameWorlds.back()->Cleanup();
		_gameWorlds.pop_back();
	}
}


GameWorld* WorldManagement::ChangeGameWorld(GameWorld *GameWorld)
{
	if (!_gameWorlds.empty())
	{
		_gameWorlds.back()->Cleanup();
		_gameWorlds.pop_back();
	}

	_gameWorlds.push_back(GameWorld);
	_gameWorlds.back()->Init();
	return _gameWorlds.back();
}

GameWorld* WorldManagement::PushSubWorld(GameWorld *GameWorld)
{
	if (!_gameWorlds.empty())
	{
		_gameWorlds.back()->Pause();
	}

	_gameWorlds.push_back(GameWorld);
	if (!GameWorld->IsInstance())
	{
		_gameWorlds.back()->Init();
	}
	return _gameWorlds.back();
}

GameWorld* WorldManagement::PopSubWorld()
{
	if (!_gameWorlds.empty())
	{
		_gameWorlds.back()->Cleanup();
		_gameWorlds.pop_back();
	}

	if (!_gameWorlds.empty())
	{
		_gameWorlds.back()->Resume();
	}
	return _gameWorlds.back();
}

GameWorld* WorldManagement::GetCurrentWorld()
{
	if (!_gameWorlds.empty())
	{
		return _gameWorlds.back();
	}

	return NULL;
}


void WorldManagement::HandleEvents(DXGame *pDXGame)
{
	_gameWorlds.back()->HandleEvents(pDXGame);
}

void WorldManagement::Update(GameTime *gameTime)
{
	if (!_gameWorlds.back()->IsFinish())
	{
		_gameWorlds.back()->Update(gameTime);
	}
	else
	{
		_isFinishWorld = true;
	}
}

void WorldManagement::Draw(DXGame *pDXGame)
{
	_gameWorlds.back()->Draw(pDXGame);
}