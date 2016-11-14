#ifndef _LINHCANH_H_
#define _LINHCANH_H_

#include "Enemy.h"
#include <math.h>

class LinhCanh : public Enemy
{
private:
	float _angle; // góc tạo đường zic zac
	float _origin_X, _origin_Y; // vị trí
	float _distance; // đoạn đường bay
public:
	LinhCanh(DXTexture *,
		D3DXVECTOR2,
		Direction = Direction::LEFT,
		D3DXVECTOR2 = D3DXVECTOR2(150, VELOCITY_FAST));
	virtual void Update(GameTime *); // Update
	virtual void Draw(DXGame *, Camera *); // Vẽ
	virtual void UpdateObjectState(GameTime *);
	//virtual void UpdateAnimation();
};

#endif