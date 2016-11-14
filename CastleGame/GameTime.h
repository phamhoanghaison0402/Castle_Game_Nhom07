#ifndef _GAMETIME_H
#define _GAMETIME_H

#include <windows.h>
#include <time.h>
#include "VariableGame.h"

class GameTime
{
	long _start, _end; // thời điểm bắt đầu, kết thúc sau mỗi lần tick
	int _elapsed;
	int _count; // thời gian mỗi Frame tồn tại 
public:
	GameTime();
	int GetElapsedTimePerFrameMiliSeconds();
	float GetElapsedTimePerFrameSeconds();
	bool CanCreateNewFrame();
};

#endif