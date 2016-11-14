#ifndef _DYNAMICOBJECT_H
#define _DYNAMICOBJECT_H

#include "BaseObject.h"

/*
Xác định hướng cho mỗi đối tượng DynamicObject.
*/
enum Direction
{
	NONE = 0,
	LEFT = 0x01,
	JUMP = 0x02,
	RIGHT = 0x04,
	FALL = 0x08
};


/*
Lớp cơ sở dành cho các đối tượng động (có thể di chuyển, chuyển động)
*/
class DynamicObject : public BaseObject
{
protected:
	int _time;
	
public:
	bool _isDead;
	Direction _direction; 
	D3DXVECTOR2 _velocity; 
	float _deltaTime; 
public:
	DynamicObject(DXTexture *pTexture, D3DXVECTOR2 position, Direction direction = Direction::LEFT, D3DXVECTOR2 velocity = D3DXVECTOR2(180, 180));
	virtual void Update(GameTime *); // Update
	virtual void Draw(DXGame *, Camera *); // Vẽ
	virtual void UpdateBound();
	virtual void UpdateObjectState(GameTime *); 
	virtual void UpdateAnimation();

	virtual bool IsDead();

	virtual RECT GetNodeBound();
	virtual Box GetNonStaticObjectBox(D3DXVECTOR2 = D3DXVECTOR2(0,0)); // trả về box với  vận tốc(_velocity - v)
	virtual Box GetBoardBox(); // trả về box với kich thước tính toán theo kiểu Board
	virtual Box GetBoardBox(D3DXVECTOR2);
};

#endif