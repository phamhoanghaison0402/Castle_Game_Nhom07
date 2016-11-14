#ifndef _OTHEROBJ_H_
#define _OTHEROBJ_H_

#include "StaticObject.h"

class Land : public StaticObject
{
public:
	Land(DXTexture *, D3DXVECTOR2);
};

class CauThang : public StaticObject
{
public:
	CauThang(DXTexture *, D3DXVECTOR2);
};

class Tower : public StaticObject
{
public:
	Tower(DXTexture *, D3DXVECTOR2);
};


class Block : public StaticObject
{
public:
	Block(DXTexture *, D3DXVECTOR2);
};


enum ESceneObject
{
	BACKGROUNDBLUE,
	DAUTRU,
	GACHDEN,
	GACHDEN_TRAI,
	GACHDO,
	GACHDO_XAM,
	GACHGIUA_DAUTRU,
	NENGACH,
	NENGACH_TRAI,
	TRU,
	TRUTIM_1,
	TRUTIM_2,
	TRUTIM_3,

	FENCE,
	MOUNTAIN,
	SIGN,
	LAMP,
	TREE,
	BIG_TREE
};

class Scene : public StaticObject
{
public:
	Scene(DXTexture *, D3DXVECTOR2, ESceneObject type);
};

#endif