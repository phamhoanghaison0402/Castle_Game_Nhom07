#include "PauseState.h"


PauseState PauseState::_instance;

void PauseState::Init()
{
	this->_menu = new PauseMenu(
		TextureManagement::GetInstance()->Get(EOTexture::PAUSEMENU_TEXTURE),
		D3DXVECTOR2(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100)
		);

	
}

void PauseState::Cleanup()
{

}

void PauseState::Pause()
{

}

void PauseState::Resume()
{
	
}


void PauseState::HandleEvents(DXGame *pDXGame)
{
	if (pDXGame->IsKeyDown(DIK_DOWN) && !_lastDownKey)
	{
		this->_menu->GoNext();
		_lastDownKey = true;
		
	}
	else if (pDXGame->IsKeyUp(DIK_DOWN))
	{
		_lastDownKey = false;
	}

	if (pDXGame->IsKeyDown(DIK_UP) && !_lastUpKey)
	{
		this->_menu->GoBack();
		_lastUpKey = true;
		
	}
	else if (pDXGame->IsKeyUp(DIK_UP))
	{
		_lastUpKey = false;
	}

	if (pDXGame->IsKeyDown(DIK_RETURN) && !_lastEnterKey)
	{
		_lastEnterKey = true;

		Info *info;
		GameWorld *curWorld;
		CastlePlayer *mario;
		GameInfo *gameInfo;
		LoadGame *load;
		PauseSelection selection = _menu->GetSelection();
		switch (selection)
		{
		case PResume:
			StateManagement::GetInstance()->PopState();
			break;
		case PLoad:
			load = new LoadGame("SaveGame");
			StateManagement::GetInstance()->PopState();
			curWorld = WorldManagement::GetInstance()->GetCurrentWorld();
			info = load->GetInfo();

			// mario
			mario = load->GetCastlePlayer();
			curWorld->SetMario(*&mario);

			// gameInfo
			gameInfo = new GameInfo(
				TextureManagement::GetInstance()->Get(EOTexture::MARIOICON_TEXTURE),
				TextureManagement::GetInstance()->Get(EOTexture::WORLD_TEXTURE),
				TextureManagement::GetInstance()->Get(EOTexture::NUMBER_TEXTURE)
				);
			gameInfo->SetScore(info->Score);
			gameInfo->SetLife(info->Life);
			gameInfo->SetWorld(info->World);
			curWorld->SetGameInfo(gameInfo);

			// info
			curWorld->_IsSubWorld = info->IsSubWorld;
			curWorld->RemoveAllSubWorld();
			curWorld->_nWorld = info->nWorld;
			
			if (info->SubWorld1 != "")
			{
				curWorld->AddSubWorld(
					new GameWorld(
					info->SubWorld1.c_str(),
					TextureManagement::GetInstance()->Get(EOTexture::BACKGROUND_TEXTURE),
					mario,
					gameInfo));
			}
			if (info->SubWorld2 != "")
			{
				curWorld->AddSubWorld(
					new GameWorld(
					info->SubWorld2.c_str(),
					TextureManagement::GetInstance()->Get(EOTexture::BACKGROUND_TEXTURE),
					mario,
					gameInfo));
			}
			curWorld->_CreepUpPos[0] = &info->CreepUpPos1;
			curWorld->_CreepUpPos[1] = &info->CreepUpPos2;
			if (info->TheNextWorld != "")
			{
				curWorld->AddTheNextWorld(
					new GameWorld(
					info->TheNextWorld.c_str(),
					TextureManagement::GetInstance()->Get(EOTexture::BACKGROUND_TEXTURE),
					mario,
					gameInfo));
			}
			curWorld->_oriMarioPos = info->OriMarioPos;

			// list object
			curWorld->_listNodes = &load->GetListQNodes();
			curWorld->_listUpdateNodes = &load->GetUpdateListQNodes();
			curWorld->_listObjects = load->GetListObjects();

			// quadtree
			curWorld->_quadTree = load->GetQuadTree();
			curWorld->_updateQuadTree = load->GetUpdateQuadTree();
			break;
		case PQuit:
			this->ChangeState(
				StateManagement::GetInstance(), 
				BeginState::GetInstance());
			break;
		default:
			break;
		}
	}
	else if (pDXGame->IsKeyUp(DIK_RETURN))
	{
		_lastEnterKey = false;
	}
}


void PauseState::Update(GameTime* gameTime)
{
	_menu->Update(gameTime);
}

void PauseState::Draw(DXGame *pDXGame)
{
	PlayState::GetInstance()->Draw(pDXGame);
	_menu->Draw(pDXGame);
}