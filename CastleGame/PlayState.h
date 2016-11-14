#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_


#include "State.h"
#include "WorldManagement.h"
#include "PauseState.h"
#include "WaitState.h"
#include "GameWorld.h"

class PlayState : public State
{
private:
	static PlayState _instance;

	CastlePlayer *_Mario;
	GameInfo *_GameInfo;

	bool _isPause;
	WorldManagement *_worldManagement;
	bool _lastEscapeKey;
	bool _flag;
protected:
	PlayState() { };
public:
	static PlayState* GetInstance()
	{
		return &_instance;
	};

	virtual void Init();
	virtual void Cleanup();

	virtual void Pause();
	virtual void Resume();

	virtual void HandleEvents(DXGame *);
	virtual void Update(GameTime*);
	virtual void Draw(DXGame *);
};

#endif