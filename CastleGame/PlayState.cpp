#include "PlayState.h"


PlayState PlayState::_instance;

void PlayState::Init()
{
	_Mario = NULL;
	_GameInfo = new GameInfo(
		TextureManagement::GetInstance()->Get(EOTexture::MARIOICON_TEXTURE),
		TextureManagement::GetInstance()->Get(EOTexture::WORLD_TEXTURE),
		TextureManagement::GetInstance()->Get(EOTexture::NUMBER_TEXTURE)
		);
	_GameInfo->SetLife(3);
	_GameInfo->SetScore(0);
	_GameInfo->SetWorld(1);

	_worldManagement = WorldManagement::GetInstance();
	GameWorld *world1 = new GameWorld("map1", TextureManagement::GetInstance()->Get(EOTexture::BACKGROUND_TEXTURE), _Mario, _GameInfo);
	world1->AddSubWorld(new GameWorld("sub1", TextureManagement::GetInstance()->Get(EOTexture::BACKGROUND_TEXTURE), _Mario, _GameInfo));


	world1->AddTheNextWorld(new GameWorld("map2", TextureManagement::GetInstance()->Get(EOTexture::BACKGROUND_TEXTURE), _Mario, _GameInfo));
	GameWorld *world2 = world1->GetTheNextWorld();
	world2->AddTheNextWorld(new GameWorld("map3", TextureManagement::GetInstance()->Get(EOTexture::BACKGROUND_TEXTURE), _Mario, _GameInfo));

	_worldManagement->ChangeGameWorld(world1);
	_isPause = false;
	_flag = false;
}

void PlayState::Cleanup()
{
	
}

void PlayState::Pause()
{
	_isPause = true;
	
}

void PlayState::Resume()
{
	_isPause = false;
	
}


void PlayState::HandleEvents(DXGame *pDXGame)
{
	if (_isPause)
		return;

	if (pDXGame->IsKeyDown(DIK_ESCAPE) && !_lastEscapeKey)
	{
		StateManagement::GetInstance()->PushState(PauseState::GetInstance());
		_lastEscapeKey = true;
	}
	else if (pDXGame->IsKeyUp(DIK_ESCAPE))
	{
		_lastEscapeKey = false;
	}

	_worldManagement->HandleEvents(pDXGame);
}


void PlayState::Update(GameTime* gameTime)
{
	if (_isPause)
		return;

	GameWorld * w = _worldManagement->GetCurrentWorld();

	if (w->IsFinish() == false)
	{
		if (w->IsGameOver() == true)
		{
			StateManagement::GetInstance()->ChangeState(WaitState::GetInstance()); // remove and change
			WaitState::GetInstance()->SetOverState(true);
		}
		else
		{
			if (w->IsReset() == false)
			{
				_worldManagement->Update(gameTime);
			}
			else
			{
				StateManagement::GetInstance()->PushState(WaitState::GetInstance()); // push
				WaitState::GetInstance()->SetLife(w->GetGameInfo()->GetLife()); // set life
				w->SetReset(false);
				w->ResetMarioPosition();
			}
		}
	}
	else
	{
		if (w != NULL)
		{
			if (w->HasTheNextWorld()) // có màn sau -> qua màn sau
			{
				WaitState::GetInstance()->SetOverState(false);
				StateManagement::GetInstance()->PushState(WaitState::GetInstance()); // push
				WaitState::GetInstance()->SetLife(w->GetGameInfo()->GetLife()); // set life

				// set world
				_Mario = w->GetMario();
				_GameInfo = w->GetGameInfo(); 
				_Mario->_position = _worldManagement->ChangeGameWorld(w->GetTheNextWorld())->_oriMarioPos;
				w->GetTheNextWorld()->SetMario(_Mario);
				w->GetTheNextWorld()->SetGameInfo(_GameInfo);
			}
			else // -> kết thúc game
			{
				StateManagement::GetInstance()->ChangeState(WaitState::GetInstance()); // remove and change
				WaitState::GetInstance()->SetOverState(true);
			}
		}
	}
}

void PlayState::Draw(DXGame *pDXGame)
{
	_worldManagement->Draw(pDXGame);
}