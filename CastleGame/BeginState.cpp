#include "BeginState.h"


BeginState BeginState::_instance;

void BeginState::Init()
{
	this->_menu = new StartMenu(
		TextureManagement::GetInstance()->Get(EOTexture::STARTMENU_TEXTURE),
		D3DXVECTOR2(50, SCREEN_HEIGHT / 2)
		);

	this->_backGround = new BaseInfo(
		TextureManagement::GetInstance()->Get(EOTexture::BEGINBACKGROUND_TEXTURE),
		D3DXVECTOR2(0, 0)
		);

	_Mario = NULL;
	_GameInfo = new GameInfo(
		TextureManagement::GetInstance()->Get(EOTexture::MARIOICON_TEXTURE),
		TextureManagement::GetInstance()->Get(EOTexture::WORLD_TEXTURE),
		TextureManagement::GetInstance()->Get(EOTexture::NUMBER_TEXTURE)
		);
	_GameInfo->SetLife(99);
	_GameInfo->SetScore(99999);
	_GameInfo->SetWorld(3);

	GameWorld *world1 = new GameWorld("mapBegin", TextureManagement::GetInstance()->Get(EOTexture::BACKGROUND_TEXTURE), _Mario, _GameInfo);
	WorldManagement::GetInstance()->ChangeGameWorld(world1);

}

void BeginState::Cleanup()
{
	
}

void BeginState::Pause()
{
	
}

void BeginState::Resume()
{

}


void BeginState::HandleEvents(DXGame *pDXGame)
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

		this->ChangeState(StateManagement::GetInstance(), PlayState::GetInstance());

		/*StartSelection selection = _menu->GetSelection();
		switch (selection)
		{
		case SStart:
			//this->ChangeState(StateManagement::GetInstance(), PlayState::GetInstance());
			break;	
		case SQuit:
			exit(0);
			break;
		default:
			break;
		}*/
	}
	else if (pDXGame->IsKeyUp(DIK_RETURN))
	{
		_lastEnterKey = false;
	}
}


void BeginState::Update(GameTime* gameTime)
{
	WorldManagement::GetInstance()->Update(gameTime);
}

void BeginState::Draw(DXGame *pDXGame)
{
	this->_backGround->Draw(pDXGame);
	WorldManagement::GetInstance()->Draw(pDXGame);
	this->_menu->Draw(pDXGame);
}