#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_


#include "WorldManagement.h"
#include "TextureManagement.h"

#include "Map.h"
#include "Camera.h"
#include "QuadTree.h"
#include "Build.h"
#include "GameInfo.h"
#include "CastlePlayer.h"
#include "Enemy.h"
#include "Brick.h"
#include "OtherObj.h"

class GameWorld
{
public:
	// sub world
	bool _IsSubWorld;
	map<int, GameWorld *> _ListSubWorld;
	int _nWorld;
	map<int, D3DXVECTOR2 *> _CreepUpPos;
	D3DXVECTOR2 _oriMarioPos; 
	// next world
	GameWorld *_TheNextWorld;

	// map = world
	char _mapFile[100];
	Map *_map;
	map<int, QNode *> *_listNodes, *_listUpdateNodes;
	QuadTree *_quadTree, *_updateQuadTree;
	map<int, BaseObject *> _listObjects;
	list<BaseObject *> _listFreeObjects;
	list<BaseObject *> _listDeadObjects;
	list<D3DXVECTOR2 *> _flagPosition;

	Camera *_camera;
	GameInfo *_gameInfo;
	CastlePlayer *mario;
	BaseInfo *_backGround;

	bool _isInstance;
	bool _isPause;
	bool _isWaitingSwitch;
	float _timeWaiting;
	bool _isFinish;
	bool _isGameOver;
	bool _isReset;

	bool _last_B;
	bool _last_ArrowUp;
	bool _last_F1, _last_F2;
public:
	GameWorld(DXTexture *);
	GameWorld(const char *, DXTexture *, CastlePlayer *&, GameInfo *&);

	virtual bool IsInstance();
	virtual void Init();
	virtual void Cleanup();

	virtual void Pause();
	virtual void Resume();

	virtual void HandleEvents(DXGame *);
	virtual void Update(GameTime *);
	virtual void Draw(DXGame *);

	virtual bool IsReset();
	virtual void SetReset(bool);
	virtual D3DXVECTOR2 GetResetPosition();
	virtual void ResetMarioPosition();
	virtual bool IsFinish();
	virtual bool IsGameOver();

	virtual void AddSubWorld(GameWorld *world);
	virtual GameWorld* GetSubWorld(int n);
	virtual void RemoveAllSubWorld();
	virtual void AddTheNextWorld(GameWorld *world);
	virtual void SetMario(CastlePlayer *&);
	virtual CastlePlayer* GetMario();
	virtual void SetGameInfo(GameInfo *&);
	virtual GameInfo* GetGameInfo();
	virtual bool HasTheNextWorld();
	virtual GameWorld* GetTheNextWorld();

	void ChangeGameWorld(WorldManagement* management, GameWorld* GameWorld) 
	{
		management->ChangeGameWorld(GameWorld);
	};
};

#endif