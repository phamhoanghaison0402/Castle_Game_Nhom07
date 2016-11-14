#ifndef _PAUSESTATE_H_
#define _PAUSESTATE_H_

#include "State.h"
#include "PauseMenu.h"
#include "PlayState.h"
#include "BeginState.h"
#include "LoadGame.h"

class PauseState : public State
{
private:
	static PauseState _instance;

	PauseMenu *_menu;
	bool _lastUpKey, _lastDownKey, _lastEnterKey;
protected:
	PauseState() { };
public:
	static PauseState* GetInstance()
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