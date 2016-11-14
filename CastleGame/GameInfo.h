#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_


#include "Number.h"


class Score : BaseInfo
{
private:
	int _score;
	Number *numbers[5];
public:
	Score(DXTexture *, D3DXVECTOR2);
	virtual void UpdateAnimation(); // Update Object
	virtual int GetScore();
	virtual bool SetScore(int);
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255)); // Vẽ Object co dinh
};


class Life : BaseInfo
{
private:
	int _life;
	Number *numbers[2];
public:
	Life(DXTexture *, DXTexture *, D3DXVECTOR2);
	virtual void UpdateAnimation(); // Update Object
	virtual int GetLife();
	virtual bool SetLife(int);
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255)); // Vẽ Object co dinh
};


class World : BaseInfo
{
private:
	int _world;
	Number *numbers[2];
public:
	World(DXTexture *, DXTexture *, D3DXVECTOR2);
	virtual void UpdateAnimation(); // Update Object
	virtual int GetWorld();
	virtual bool SetWorld(int);
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255)); // Vẽ Object co dinh
};


class GameInfo
{
	Score *_score;
	Life *_life;
	World *_world;
public:
	GameInfo(DXTexture *, DXTexture *, DXTexture *);
	virtual void Draw(DXGame *, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255)); // Vẽ Object co dinh
	virtual int GetScore();
	virtual bool SetScore(int);
	virtual int GetWorld();
	virtual bool SetWorld(int);
	virtual int GetLife();
	virtual bool SetLife(int);
	virtual void LifeUp();
	virtual void LifeDown();
	virtual void AddScore(int);
	virtual void WorldUp();
};

#endif