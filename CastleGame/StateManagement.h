#ifndef _STATEMANAGEMENT_H_
#define _STATEMANAGEMENT_H_


#include <vector>
#include "DirectXGame.h"
#include "Camera.h"
#include "GameTime.h"
#include "TextureManagement.h"

using namespace std;

class State;

class StateManagement
{
private:
	vector<State *> states;
	static StateManagement _instance;

	StateManagement() {};
public:
	static StateManagement* GetInstance()
	{
		return &_instance;
	};

	void Init();
	void Cleanup();

	void ChangeState(State *);
	void ChangeState(State *, bool);
	void PushState(State *);
	void PopState();

	void HandleEvents(DXGame *);
	void Update(GameTime *);
	void Draw(DXGame *);
};


#endif