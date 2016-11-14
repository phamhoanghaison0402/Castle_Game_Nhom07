#ifndef _DIRECTXGAME_H_
#define _DIRECTXGAME_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>
#include "DSutil.h"
#include "Logger.h"

#include "VariableGame.h"


class DXGame;
class DXSurface;
class DXTexture;


class DXGame
{
private: 
	static LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); 
protected:
	HWND _hWnd;

	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3dDevice;
	LPDIRECT3DSURFACE9 _backBuffer;
	LPD3DXSPRITE _spriteHandler;

	LPDIRECTINPUT8 _input;
	LPDIRECTINPUTDEVICE8 _keyboardDevice;
	char keys[256];

	LPDIRECTSOUND8 _pDS;

public:
	DXGame();
	bool Init_Window(HINSTANCE);
	bool Init_Direct3D();
	bool BeginScene();
	void Clear();
	void DrawSurface(DXSurface *, RECT * = NULL, RECT * = NULL);
	void SpriteHandler_Begin();
	void DrawTexture(DXTexture *, D3DXVECTOR2 *, float, float, RECT * = NULL, D3DCOLOR = D3DCOLOR_XRGB(255,255,255));
	void DrawTexture(DXTexture *, D3DXVECTOR2 *, RECT * = NULL, D3DCOLOR = D3DCOLOR_XRGB(255,255,255));
	void SpriteHandler_End();
	void EndScene();
	void Present();
	void DeleteWindow();
	void DeleteDirect3D();
	void DeleteKeyboard();

	bool Init_Input();
	bool Init_KeyboardDevice();
	void PollKeyboard();
	bool IsKeyDown(int);
	bool IsKeyUp(int);

	bool InitDirectSound(HWND hwnd);
	void ShutdownDirectSound(void);
	~DXGame();
};





class DXSurface
{
private:
	LPDIRECT3DSURFACE9 _surface;
	D3DXIMAGE_INFO _info;
	LPDIRECT3DDEVICE9 _d3dDevice;
public:
	DXSurface(LPDIRECT3DDEVICE9);
	bool LoadSurface(char *, D3DCOLOR = 0);
	LPDIRECT3DSURFACE9 GetSurface();
	int GetWidth();
	int GetHeight();
	~DXSurface();
};




class DXTexture
{
private:
	LPDIRECT3DDEVICE9 _d3dDevice;
	LPDIRECT3DTEXTURE9 _texture;
	D3DXIMAGE_INFO _info;
	int _width, _height;
public:
	DXTexture(LPDIRECT3DDEVICE9);
	bool LoadTexture(char *, float, float, D3DCOLOR = 0);
	bool LoadTexture(char *, D3DCOLOR = 0);
	LPDIRECT3DTEXTURE9 GetTexture();
	int GetWidth();
	int GetHeight();
	~DXTexture();
};


class DXSoundBuffer
{
private:
	LPDIRECTSOUNDBUFFER _soundBuffer;
	LPDIRECTSOUND8 _pDS;
public:
	DXSoundBuffer(LPDIRECTSOUND8 pDS);
	bool LoadWaveToSoundBuffer(std::string wavFilename);
	LPDIRECTSOUNDBUFFER getSoundBuffer();
	void Play();
	void PlayLoop();
	void Stop();
	~DXSoundBuffer();
};

#endif