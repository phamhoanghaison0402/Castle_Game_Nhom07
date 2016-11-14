#ifndef _SettingState_H_
#define _SettingState_H_

#include "State.h"
#include "BeginState.h"


class SettingState : public State
{
private:
	static SettingState _instance;

	BaseInfo *_backGround;
	bool _lastESCKey; 
	bool _lastUpKey, _lastDownKey, _lastLeftKey, _lastRightKey;
protected:
	SettingState() { };
public:
	static SettingState* GetInstance()
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