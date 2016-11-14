#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3dx9.h>
#include "VariableGame.h"

class Camera
{
public:
	float _X, _Y, _lastY, _hY;

	D3DXMATRIX _matrix;
	RECT _rect;
public:
	Camera();
	void Update(D3DXVECTOR2 marioPos);
};

#endif