#include "StateManagement.h"
#include "State.h"


StateManagement StateManagement::_instance = StateManagement();

void StateManagement::Init()
{

}

void StateManagement::Cleanup()
{
	while (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}
}


void StateManagement::ChangeState(State *state)
{
	if (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}

	states.push_back(state);
	states.back()->Init();
}

void StateManagement::PushState(State *state)
{
	if (!states.empty())
	{
		states.back()->Pause();
	}

	states.push_back(state);
	states.back()->Init();
}

void StateManagement::PopState()
{
	if (!states.empty())
	{
		states.back()->Cleanup();
		states.pop_back();
	}

	if (!states.empty())
	{
		states.back()->Resume();
	}
}


void StateManagement::HandleEvents(DXGame *pDXGame)
{
	states.back()->HandleEvents(pDXGame);
}

void StateManagement::Update(GameTime *gameTime)
{
	states.back()->Update(gameTime);
}

void StateManagement::Draw(DXGame *pDXGame)
{
	states.back()->Draw(pDXGame);
}