#include "DirectXGame.h"

DXGame::DXGame()
{
	this->_d3d = NULL;
	this->_d3dDevice = NULL;
	this->_backBuffer = NULL;
	this->_pDS = NULL;
}

LRESULT WINAPI DXGame::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool DXGame::Init_Window(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize		 = sizeof(WNDCLASSEX);

	wc.style		 = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	 = (WNDPROC)DXGame::WinProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); //(HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName  = NULL;
	wc.lpszClassName = GAME_TITLE;
    wc.hIconSm       = NULL;

	RegisterClassEx(&wc);

	DWORD style;
	if (FULL_SCREEN)
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
    else
	{
        style = WS_OVERLAPPEDWINDOW;
	}

	_hWnd = CreateWindow(
		GAME_TITLE,
		GAME_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!_hWnd)
	{
		(Logger::GetLogger("DXGame::Init_Window(HINSTANCE)").Error("Can't Init Window"));
		return false;
	}

	ShowWindow(_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(_hWnd);

	return true;
}

bool DXGame::Init_Direct3D()
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (_d3d == NULL)
	{
		(Logger::GetLogger("DXGame::Init_Direct3D()").Error("Can't Init DirectX Object"));
		return false;
	}

	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	
	pp.Windowed = !FULL_SCREEN;
	pp.SwapEffect = D3DSWAPEFFECT_COPY;
	//pp.BackBufferFormat = D3DFMT_X8R8G8B8;
	pp.BackBufferCount = 1;
	pp.BackBufferWidth = SCREEN_WIDTH;
	pp.BackBufferHeight = SCREEN_HEIGHT;
	pp.hDeviceWindow = _hWnd;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	
	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&pp,
		&_d3dDevice);

	if (_d3dDevice == NULL)
	{
		(Logger::GetLogger("DXGame::Init_Direct3D()").Error(""));
		return false;
	}

	_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	_d3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_backBuffer);

	if (D3DXCreateSprite(_d3dDevice, &_spriteHandler) != D3D_OK)
	{
		(Logger::GetLogger("DXGame::Init_Direct3D()").Error("Can't Init Sprite"));
		return false;
	}

	return true;
}

bool DXGame::BeginScene()
{
	return _d3dDevice->BeginScene();
}

void DXGame::Clear()
{
	_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0);
}

void DXGame::DrawSurface(DXSurface *pSurface, RECT *pSourceRect, RECT *PDestRect)
{
	_d3dDevice->StretchRect(pSurface->GetSurface(), pSourceRect, _backBuffer, PDestRect, D3DTEXF_NONE);
}

void DXGame::SpriteHandler_Begin()
{
	_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
}

void DXGame::DrawTexture(DXTexture *pTexture, D3DXVECTOR2 *pCenter, float width, float height, RECT *pSourceRect, D3DCOLOR color)
{
	_spriteHandler->Draw(pTexture->GetTexture(), pSourceRect, &D3DXVECTOR3(width/2, height/2, 0), &D3DXVECTOR3(pCenter->x, pCenter->y, 0), color);
}

void DXGame::DrawTexture(DXTexture *pTexture, D3DXVECTOR2 *pPos, RECT *pSourceRect, D3DCOLOR color)
{
	D3DXVECTOR3 pos;
	pos = D3DXVECTOR3(pPos->x, pPos->y, 0);

	_spriteHandler->Draw(pTexture->GetTexture(), pSourceRect, NULL, &pos, color);
	//_spriteHandler->Draw(pTexture->GetTexture(), pSourceRect, &D3DXVECTOR3(pos.x/2, pos.y/2, 0), &D3DXVECTOR3(0, 0, 0), color);
}
void DXGame::SpriteHandler_End()
{
	_spriteHandler->End();
}


void DXGame::EndScene()
{
	_d3dDevice->EndScene();
}

void DXGame::Present()
{
	_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void DXGame::DeleteWindow()
{
	if (_hWnd)
	{
		DestroyWindow(_hWnd);
	}
}

void DXGame::DeleteDirect3D()
{
	if (_backBuffer != NULL)
	{
		_backBuffer->Release();
		_backBuffer = NULL;
	}

	if (_d3dDevice != NULL)
	{
		_d3dDevice->Release();
		_d3dDevice = NULL;
	}

	if (_d3d != NULL)
	{
		_d3d->Release();
		_d3d = NULL;
	}
}

bool DXGame::Init_Input()
{
	HRESULT result;
	result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&_input,
		NULL);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXGame::Init_Input()").Error("Can't Init DirectX Input"));
		return false;
	}

	result = _input->CreateDevice(GUID_SysKeyboard, &_keyboardDevice, NULL);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXGame::Init_Input()").Error("Can't Init DirectX Input Device"));
		return false;
	}

	return true;
}

bool DXGame::Init_KeyboardDevice()
{
	HRESULT result;
	result = _keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXGame::Init_KeyboardDevice()").Error("Can't Set Data Format Keyboard"));
		return false;
	}

	result = _keyboardDevice->SetCooperativeLevel(_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXGame::Init_KeyboardDevice()").Error("Can't Set Cooperative Level Keyboard"));
		return false;
	}

	result = _keyboardDevice->Acquire();
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXGame::Init_KeyboardDevice()").Error("Can't Acquire Keyboard"));
		return false;
	}

	return true;
}

void DXGame::PollKeyboard()
{
	_keyboardDevice->Poll();
	if (FAILED(_keyboardDevice->GetDeviceState(sizeof(keys),(LPVOID)&keys)))
    {
        //keyboard device lost, try to re-acquire
        _keyboardDevice->Acquire();
        _keyboardDevice->GetDeviceState(sizeof(keys),(LPVOID)&keys);
    }
	else
	{
		_keyboardDevice->GetDeviceState(sizeof(keys), (LPVOID)&keys);
	}
	
}

bool DXGame::IsKeyDown(int key)
{
	if (keys[key] & 0x80)
		return true;
	return false;
}

bool DXGame::IsKeyUp(int key)
{
	if (keys[key] & 0x80)
		return false;
	return true;
}

void DXGame::DeleteKeyboard()
{
	if (_keyboardDevice != NULL)
	{
		_keyboardDevice->Unacquire();
		_keyboardDevice->Release();
		_keyboardDevice = NULL;
	}
}

void DXGame::ShutdownDirectSound(void)
{
	if (_pDS != NULL)
	{
		_pDS->Release();
		_pDS = NULL;
	}
}

bool DXGame::InitDirectSound(HWND hwnd)
{
	HRESULT hr;

	hr = DirectSoundCreate8( NULL, &_pDS, NULL );
	if FAILED (hr)
		return false;

	// Set DirectSound cooperative level 
    hr = _pDS->SetCooperativeLevel( hwnd, DSSCL_PRIORITY );
	if FAILED ( hr )
		return false;

	return true;
}

DXGame::~DXGame()
{
	DeleteKeyboard();
	DeleteDirect3D();
	DeleteWindow();
	ShutdownDirectSound();
}




DXSurface::DXSurface(LPDIRECT3DDEVICE9 device)
{
	this->_d3dDevice = device;
	this->_surface = NULL;
}

bool DXSurface::LoadSurface(char *filename, D3DCOLOR color)
{
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &_info);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXSurface::LoadSurface(char*, D3DCOLOR)").Error("Can't Get Image Info From File"));
		return false;
	}

	result = _d3dDevice->CreateOffscreenPlainSurface(
		_info.Width,
		_info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&_surface,
		NULL);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXSurface::LoadSurface(char*, D3DCOLOR)").Error("Can't Create Off Screen Plain Surface"));
		return false;
	}

	result = D3DXLoadSurfaceFromFile(
		_surface,
		NULL,
		NULL,
		filename,
		NULL,
		D3DX_DEFAULT,
		color,
		NULL);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXSurface::LoadSurface(char*, D3DCOLOR)").Error("Can't Load Surface From File"));
		return false;
	}

	return true;
}

LPDIRECT3DSURFACE9 DXSurface::GetSurface()
{
	return this->_surface;
}

int DXSurface::GetWidth()
{
	return _info.Width;
}

int DXSurface::GetHeight()
{
	return _info.Height;
}

DXSurface::~DXSurface()
{
	if (_surface != NULL)
	{
		_surface->Release();
		_surface = NULL;
	}
}




DXTexture::DXTexture(LPDIRECT3DDEVICE9 device)
{
	this->_d3dDevice = device;
	this->_texture = NULL;
}

bool DXTexture::LoadTexture(char *filename, float nHorizontal, float nVertical, D3DCOLOR color)
{
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &_info);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXTexture::LoadTexture(LPDIRECT3DDEVICE9)").Error("Can't Get Image Info From File"));
		return false;
	}

	_width = (int)(nHorizontal * (float)OBJECT_WIDTH);
	_height = (int)(nVertical * (float)OBJECT_HEIGHT);
	result = D3DXCreateTextureFromFileEx(
		_d3dDevice,
		filename,
		_width,
		_height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		&_info,
		NULL,
		&_texture);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXTexture::LoadTexture(LPDIRECT3DDEVICE9)").Error("Can't Create Texture From File"));
		_texture = NULL;
		return false;
	}

	return true;
}

bool DXTexture::LoadTexture(char *filename, D3DCOLOR color)
{
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &_info);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXTexture::LoadTexture(char*, D3DCOLOR)").Error("Can't Get Image Info From File"));
		return false;
	}

	_width = _info.Width;
	_height = _info.Height;
	result = D3DXCreateTextureFromFileEx(
		_d3dDevice,
		filename,
		_info.Width,
		_info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		&_info,
		NULL,
		&_texture);
	if (result != D3D_OK)
	{
		(Logger::GetLogger("DXTexture::LoadTexture(char*, D3DCOLOR)").Error("Can't Create Texture From File"));
		_texture = NULL;
		return false;
	}

	return true;
}


LPDIRECT3DTEXTURE9 DXTexture::GetTexture()
{
	return this->_texture;
}

int DXTexture::GetWidth()
{
	return _width;
}

int DXTexture::GetHeight()
{
	return _height;
}

DXTexture::~DXTexture()
{
	if (_texture != NULL)
	{
		_texture->Release();
		_texture = NULL;
	}
}




DXSoundBuffer::DXSoundBuffer(LPDIRECTSOUND8 pDS)
{
	this->_pDS = pDS;
	this->_soundBuffer = NULL;
}

bool DXSoundBuffer::LoadWaveToSoundBuffer(std::string wavFilename)
{
	CWaveFile *wavFile;
	HRESULT hr;

	wavFile = new CWaveFile();
	wavFile->Open((char*)wavFilename.c_str(), NULL, WAVEFILE_READ );
	if( wavFile->GetSize() == 0 )
	{
		(Logger::GetLogger("DXSoundBuffer::LoadWaveToSoundBuffer(std::string wavFilename)").Error("Invalid file!"));
		return false;
	}

	DSBUFFERDESC dsbd;
    ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
    dsbd.dwSize          = sizeof(DSBUFFERDESC);
    //dsbd.dwFlags         = 0;
	dsbd.dwFlags         = DSBCAPS_CTRLVOLUME;
    dsbd.dwBufferBytes   = wavFile->GetSize();
    dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat     = wavFile->m_pwfx;

	hr = _pDS->CreateSoundBuffer( &dsbd, &_soundBuffer, NULL );
	if FAILED (hr)
	{
		(Logger::GetLogger("DXSoundBuffer::LoadWaveToSoundBuffer(std::string wavFilename)").Error("Unable to create sound buffer!"));
		return false;
	}

	VOID*   pDSLockedBuffer      = NULL; // Pointer to locked buffer memory
    DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
    DWORD   dwWavDataRead        = 0;    // Amount of data read from the wav file 
	
	hr = _soundBuffer->Lock( 0, wavFile->GetSize(), 
						   &pDSLockedBuffer, &dwDSLockedBufferSize, 
                           NULL, NULL, 0L );
	if FAILED (hr)
        return false;

    // Reset the wave file to the beginning 
    wavFile->ResetFile();

	// Read the wave file
    hr = wavFile->Read( (BYTE*) pDSLockedBuffer,
                       dwDSLockedBufferSize, 
                       &dwWavDataRead );
	// Check to make sure that this was successful
	if FAILED (hr)
        return false;

	// Check to make sure the wav file is not empty
    if( dwWavDataRead == 0 )
    {
        // Wav is blank, so just fill with silence
        FillMemory( (BYTE*) pDSLockedBuffer, 
                    dwDSLockedBufferSize, 
                    (BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0 ) );
    }
    else if( dwWavDataRead < dwDSLockedBufferSize )
    {
	    // Don't repeat the wav file, just fill in silence 
        FillMemory( (BYTE*) pDSLockedBuffer + dwWavDataRead, 
                   dwDSLockedBufferSize - dwWavDataRead, 
                   (BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0 ) );
    }

    // Unlock the buffer, we don't need it anymore.
	_soundBuffer->Unlock( pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0 );

	// Clean up
	delete wavFile;

	return true;
}

void DXSoundBuffer::Play()
{
	this->_soundBuffer->Play( 0, 0, 0);
}

void DXSoundBuffer::PlayLoop()
{
	this->_soundBuffer->Play( 0, 0, DSBPLAY_LOOPING );
}

void DXSoundBuffer::Stop()
{
	this->_soundBuffer->Stop();
}

DXSoundBuffer::~DXSoundBuffer()
{
	if (_soundBuffer != NULL)
	{
		_soundBuffer->Release();
		_soundBuffer = NULL;
	}
}

LPDIRECTSOUNDBUFFER DXSoundBuffer::getSoundBuffer()
{
	return _soundBuffer;
}