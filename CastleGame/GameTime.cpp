#include "GameTime.h"


GameTime::GameTime()
{
	_end = timeGetTime();
	_start = _end;
	_count = 0;
}

int GameTime::GetElapsedTimePerFrameMiliSeconds()
{
	if (_elapsed > 20)
	{
		_elapsed = 20;
	}

	return _elapsed;
}

float GameTime::GetElapsedTimePerFrameSeconds()
{
	if (_elapsed > 20)
	{
		_elapsed = 20;
	}

	return _elapsed / 1000.0f;
}

bool GameTime::CanCreateNewFrame()
{
	_start = _end;
	_end = timeGetTime();

	_count += _end - _start;
	if (_count >= 1000/FRAME_NUMBER)
	{
		_elapsed = _count;
		_count = 0;
		return true;
	}

	return false;
}