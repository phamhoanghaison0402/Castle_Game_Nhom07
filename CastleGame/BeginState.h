#ifndef _BEGINSTATE_H_
#define _BEGINSTATE_H_

#include "State.h"
#include "StartMenu.h"
#include "PlayState.h"
#include "SettingState.h"
#include "GameInfo.h"
#include "CastlePlayer.h"


class BeginState : public State
{
private:
	static BeginState _instance;

	CastlePlayer *_Mario;
	GameInfo *_GameInfo;

	StartMenu *_menu;
	BaseInfo *_backGround;
	bool _lastUpKey, _lastDownKey, _lastEnterKey;
protected:
	BeginState() { };
public:
	static BeginState* GetInstance()
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