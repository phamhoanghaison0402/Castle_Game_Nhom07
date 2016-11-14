#include "CastleGame.h"


CastleGame::CastleGame() : DXGame()
{}

bool CastleGame::Init(HINSTANCE hInstance)
{
	if (!Init_Window(hInstance))
	{
		(Logger::GetLogger("MarioGame::Init(HINSTANCE)").Error("Can't Init Window"));
		return false;
	}

	if (!Init_Direct3D())
	{
		(Logger::GetLogger("MarioGame::Init(HINSTANCE)").Error("Can't Init DirectX"));
		return false;
	}

	if (!Init_Input())
	{
		(Logger::GetLogger("MarioGame::Init(HINSTANCE)").Error("Can't Init Input"));
		return false;
	}

	if (!Init_KeyboardDevice())
	{
		(Logger::GetLogger("MarioGame::Init(HINSTANCE)").Error("Can't Init Keyboard"));
		return false;
	}

	if (!InitDirectSound(_hWnd))
	{
		//log
		return false;
	}

	Initialize();

	return true;
}

void CastleGame::Run()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			PollKeyboard();
			if (gameTime->CanCreateNewFrame())
			{
				Update();

				if (this->BeginScene())
				{
					// draw surface background
					//this->DrawSurface(background);

					this->Clear();

					this->SpriteHandler_Begin();

					Draw();

					this->SpriteHandler_End();

					this->EndScene();
				}

				this->Present();
			}
		}
	}
}

void CastleGame::End()
{
	DeleteWindow();
	DeleteDirect3D();
	DeleteWindow();
	ShutdownDirectSound();
}

void CastleGame::Initialize()
{
	gameTime = new GameTime();

	// texture
	textureManagement = TextureManagement::GetInstance();
	textureManagement->AddAll(this->_d3dDevice);

	// state
	stateManagement = StateManagement::GetInstance();
	stateManagement->Init();
	stateManagement->PushState(BeginState::GetInstance());
}

void CastleGame::Update()
{
	stateManagement->HandleEvents(this);
	stateManagement->Update(gameTime);
}

void CastleGame::Draw()
{
	stateManagement->Draw(this);
}