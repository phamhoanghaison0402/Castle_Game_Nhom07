#include "WaitState.h"


WaitState WaitState::_instance;

void WaitState::Init()
{
	_waitScreen = new WaitScreen(
		TextureManagement::GetInstance()->Get(EOTexture::WAITSCREEN_TEXTURE), 
		TextureManagement::GetInstance()->Get(EOTexture::NUMBER_TEXTURE)
		);

	_overScreen = new GameOverScreen(
		TextureManagement::GetInstance()->Get(EOTexture::GAMEOVERSCREEN_TEXTURE)
		);

	//_waitScreen->SetLife(3);
	_time = 0;
	_isOverState = false;
}

void WaitState::Cleanup()
{

}

void WaitState::Pause()
{

}

void WaitState::Resume()
{

}


void WaitState::HandleEvents(DXGame *pDXGame)
{

}


void WaitState::Update(GameTime* gameTime)
{
	_time += gameTime->GetElapsedTimePerFrameMiliSeconds();
	if (_time > TIME_OF_CHANGING_WORLD)
	{
		_time = 0;
		if (!_isOverState)
		{
			StateManagement::GetInstance()->PopState(); // pop -> quay lại trạng thái play
		}
		else
		{
			StateManagement::GetInstance()->ChangeState(BeginState::GetInstance()); // change -> begin
		}
	}
}

void WaitState::Draw(DXGame *pDXGame)
{
	if (!_isOverState)
	{
		_waitScreen->Draw(pDXGame);
	}
	else
	{
		_overScreen->Draw(pDXGame);
	}
}

void WaitState::SetOverState(bool flag)
{
	_isOverState = flag;
}

bool WaitState::IsOverState()
{
	return _isOverState;
}

void WaitState::SetLife(int value)
{
	_waitScreen->SetLife(value);
}