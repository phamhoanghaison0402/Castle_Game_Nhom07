#ifndef _WaitState_H_
#define _WaitState_H_

#include "State.h"
#include "WaitScreen.h"
#include "GameOverScreen.h"
#include "BeginState.h"


class WaitState : public State
{
private:
	static WaitState _instance;

	WaitScreen *_waitScreen;
	GameOverScreen *_overScreen;
	float _time;
	bool _isOverState;
protected:
	WaitState() { };
public:
	static WaitState* GetInstance()
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

	virtual void SetOverState(bool);
	virtual bool IsOverState();
	virtual void SetLife(int);
};

#endif