#ifndef _BRICK_H_
#define _BRICK_H_

// Need to edit

#include "CastlePlayer.h"

class Coin;

class Brick : public DynamicObject
{
private:
	DynamicObject *_pFraments[4];
	D3DXVECTOR2 _a; // gia tốc
	int _time;
public:
	bool _isColFirst;
	float _origin_Y;
	bool _isExplored; // bị nổ (vỡ) (no coin) hoặc biến thành block (hascoin)
	bool _isCollision; // kiểm tra sự va chạm vs mario (hascoin)
	bool _isMovedUp; // bị đẩy lên(not has coin) hoặc xuất hiện đồng coin (hascoin).
	bool _isDisappear; // no coin
	bool _hasCoin;
	Coin *_coin;
public:
	Brick(DXTexture *, DXTexture *, D3DXVECTOR2, DXTexture * = NULL, bool = false);
	virtual void Update(GameTime *);
	virtual void Draw(DXGame *, Camera *);
	virtual void UpdateObjectState(GameTime *);
	virtual void UpdateAnimation();
	
	virtual void HasCollision();
	~Brick();
};

#endif