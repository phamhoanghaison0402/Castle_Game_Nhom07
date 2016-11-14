#ifndef _MARIOPLAYER_H_
#define _MARIOPLAYER_H_

#include "DynamicObject.h"
#include "Collision.h"
#include <list>
#include"Boomerang.h"


enum CastleType
{
	CASTLE_WALK,
	CASTLE_SIT,
	CASTLE_BULLET,
};


class CastlePlayer : public DynamicObject, public Collision
{
public:
	DXTexture *_pSmallTexture, *_pNormalTexture, *_pSuperTexture, *_pBulletTexture;
	
	D3DXVECTOR2 _maxV;
	D3DXVECTOR2 _a, _maxA;

	float _timeToGrownUp; 
	//MarioType _lastType; 
	
	D3DXCOLOR _color;
	float _timeImr, _totalTimeImr;
	int _nImr;

	float _vel_X, _vel_Y;

	int _nBullet;
	bool _throwBullet;
public:
	bool _SMoveLeft, _SMoveRight, _SJump, _SFall, _SDie;
	bool _Run, _Sit, _Roi;

	bool _IsImmortality; 
	bool _EatMushroom, _EatFlower, _IsSmaller;
	CastleType _Type;

	Boomerang *_Bullet[3];

public:
	CastlePlayer(
		DXTexture *pTexture, 
		DXTexture *pNormalTexture, 
		DXTexture *pSuperTexture, 
		DXTexture *pBulletTexture, 
		D3DXVECTOR2 position, 
		CastleType type,
		D3DXVECTOR2 velocity = D3DXVECTOR2(20, 20), 
		D3DXVECTOR2 a = D3DXVECTOR2(1000, -2000));

	virtual void Update(GameTime *);
	virtual void Draw(DXGame *pDXGame, Camera *);
	virtual void UpdateBullets(GameTime *);
	virtual void DrawBullets(DXGame *pDXGame, Camera *);
	virtual bool CheckBulletsCollision(BaseObject *);
	virtual void ThrowBullet(list<BaseObject *> &);
	virtual void UpdateBound();
	virtual void UpdateObjectState(GameTime *);
	virtual void UpdateMoving();
	virtual void UpdateAnimation();
	virtual Box GetBoardBox();
	virtual Box GetBoardBox(D3DXVECTOR2);
	virtual void TransferPosition(float, float);

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void NoneMove();
	virtual void Jump();
	virtual void Jump(float vy);
	virtual void Run();
	virtual void NoneRun();
	virtual void Sit();
	virtual void NoneSit();
	virtual void PhongRoi();
	virtual void NonePhongRoi();

	virtual void ResponseCollisionsWithEnemy();
	virtual void Immortality();
	

	virtual void BeginToCheckCollisions();
	virtual void TopCol(BaseObject *obj);
	virtual void BottomCol(BaseObject *obj);
	virtual void LeftCol(BaseObject *obj);
	virtual void RightCol(BaseObject *obj);
	virtual CollisionDirection CheckCollisions(BaseObject *);
	virtual void ResponseCollisions();
	virtual void ResponseAsNoCollision(BaseObject *, CollisionDirection);
};

#endif