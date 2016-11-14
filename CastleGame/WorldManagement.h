#ifndef _WorldManagement_H_
#define _WorldManagement_H_


#include <vector>
#include "DirectXGame.h"
#include "Camera.h"
#include "GameTime.h"

using namespace std;

class GameWorld;

class WorldManagement
{
private:
	vector<GameWorld *> _gameWorlds;
	static WorldManagement _instance;

	bool _isFinishWorld;

	WorldManagement() {};
public:
	static WorldManagement* GetInstance()
	{
		return &_instance;
	};

	void Init();
	void Cleanup();

	GameWorld* ChangeGameWorld(GameWorld *);
	GameWorld* PushSubWorld(GameWorld *);
	GameWorld* PopSubWorld();
	GameWorld* GetCurrentWorld();

	void HandleEvents(DXGame *);
	void Update(GameTime *);
	void Draw(DXGame *);
};



#endif