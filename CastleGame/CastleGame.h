#ifndef _CastleGame_H_
#define _CastleGame_H_

#include "DirectXGame.h"
#include "Map.h"
#include "Camera.h"
#include "QuadTree.h"


#include "CastlePlayer.h"
#include "Brick.h"
#include "Enemy.h"
#include "OtherObj.h"

#include "PauseMenu.h"
#include "GameInfo.h"
#include "WaitScreen.h"
#include "GameOverScreen.h"
#include "StartMenu.h"

#include "TextureManagement.h"
#include "StateManagement.h"
#include "BeginState.h"


class CastleGame : public DXGame
{
	GameTime *gameTime;
	Camera *camera;

	TextureManagement *textureManagement;
	StateManagement *stateManagement;

	/*
	Map *m;
	QuadTree *quadTree;
	map<int, BaseObject *> listObjects;
	*/

	PauseMenu *pauseMenu;
	//StartMenu *startMenu;
	/*
	Score *score;
	Life *life;
	World *world;
	GameInfo *gameInfo;*/
	WaitScreen *wait;
	GameOverScreen *gameOver;

	/*
	DXSurface *background;
	DXTexture *texture, *texture1, *texture2;
	//MarioPlayer *mario;
	DXTexture *bulletTexture;

	DXSoundBuffer *sound1, *sound2;

	DXTexture *pauseTexture, *startTexture, *numberTexture, *lifeTexture, *worldTexture, *waitTexture, *gameOverTexture;
	DXTexture *brickTexture, *blockTexture, *exploredBrickTexture, *coinTexture, *mushroomTexture, *flowerTexture, *grassTexture, *cloudTexture, *carnivorousFlowerTexture, *barTexture, *enemyTexture, *turtleTexture, *secretBlockTexture, *pipeTexture, *landTexture;
	DXTexture *starTexture;
	*/
	
	/*Brick *brick;
	Coin *coin;
	Flower *flower;
	Grass *grass;
	Cloud *cloud;
	CarnivorousFlower *carnivorousFlower;
	Bar *bar;
	Mushroom *mushroom;
	Enemy *enemy;
	Turtle *turtle;
	SecretBlock *secretBlock;
	Pipe *pipe;
	Land *land;*/

public:
	CastleGame();
	bool Init(HINSTANCE);
	void Run();
	void End();
	void Initialize();
	void Update();
	void Draw();
	~CastleGame();
};

#endif