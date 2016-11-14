#ifndef _STATE_H_
#define _STATE_H_


#include "StateManagement.h"


class State
{
protected:
	State() { }
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(DXGame *) = 0;
	virtual void Update(GameTime *) = 0;
	virtual void Draw(DXGame *) = 0;

	void ChangeState(StateManagement* management, State* state) 
	{
		management->ChangeState(state);
	};
};


#endif