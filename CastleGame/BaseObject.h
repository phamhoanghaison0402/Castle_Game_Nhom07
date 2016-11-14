#ifndef _BASEOBJECT_H
#define _BASEOBJECT_H

#include "DirectXGame.h"
#include "GameTime.h"
#include "Camera.h"
#include "SweptAABB.h"

static bool Intersect(const RECT *rect1, const RECT *rect2)
{
	if (rect1 == NULL || rect2 == NULL)
		return false;

	if (rect1->right < rect2->left) // _rect bên trái so với obj->_rect
		return false;
	if (rect1->left > rect2->right) // _rect bên phải so với obj->_rect
		return false;
	if (rect1->bottom > rect2->top) // _rect bên trên so với obj->_rect
		return false;
	if (rect1->top < rect2->bottom) // _rect bên dưới so với obj->_rect
		return false;

	return true;
}

static Box ConvertRectToBox(RECT rect, float vx = 0.0f, float vy = 0.0f)
{
	Box box(
		rect.left, 
		rect.top, 
		rect.right - rect.left,
		rect.top - rect.bottom,
		vx,
		vy
		);

	return box;
}

static Box ConvertRectToBoardBox(RECT rect, float vx = 0.0f, float vy = 0.0f)
{
	return GetSweptBroadphaseBox(ConvertRectToBox(rect, vx, vy));
}


enum EObjectName
{
    NONE_OBJECT = 0,
    MARIO_OBJECT = 1,

	//Enemy
	BOSS_1_OBJECT,
	BANCHONG_OBJECT,
	CHO_OBJECT,
	DAULAU_OBJECT,
	DAUQUAI_OBJECT,
	DOI_OBJECT,
	ECH_OBJECT,
	LINHCANH_OBJECT,
	MA_OBJECT,
	NGUOIECH_OBJECT,

	//Item
	BINHVANG_OBJECT,
	DAYCHUYEN_OBJECT,
	DUIGA_OBJECT,
	NGOC_OBJECT,
	NUOCTHANH_OBJECT,
	RUONG_OBJECT,
	TRAITIM_LON_OBJECT,
	TRAITIM_NHO_OBJECT,
	TUITIEN_TRANG_OBJECT,
	TUITIEN_XANH_OBJECT,
	VUONGMIENG_OBJECT,

	// orther
	BACKGROUND_BLUE_OBJECT,
	CAUTHANG_OBJECT,
	CANHCUA_OBJECT,
	DAUTRU_OBJECT,
	DAUTRU_TRAI_OBJECT,
	GACHDEN_OBJECT,
	GACHDEN_TRAI_OBJECT,
	GACHDO_OBJECT,
	GACHDO_XAM_OBJECT,
	GACHGIUA_DAUTRU_OBJECT,
	GACHNAU_OBJECT,
	NENGACH_OBJECT,
	NENGACH_TRAI_OBJECT,
    NGONDUOC_OBJECT,
    NGONNEN_OBJECT,
	THANHTRUOT_OBJECT,
	TRU_OBJECT,
	TRUTIM_1_OBJECT,
	TRUTIM_2_OBJECT,
	TRUTIM_3_OBJECT,

    TOWER_OBJECT,
	BULLET_OBJECT,
};

/*
Lớp cơ sở cho tất cả các đối tượng trong game.
*/
class BaseObject
{
public:
	EObjectName _OType;
	DXTexture *_texture; // texture
	int _offset_X, _offset_Y; // xác định frame
	RECT _rectSource; // HCN thể hiện frame animation đối tượng
public:
	int _width, _height; // kích thước
	RECT _rect;
	D3DXVECTOR2 _position; // vị trí
public:
	BaseObject(DXTexture *, D3DXVECTOR2);
	virtual void Update(GameTime *); // Update Object
	virtual void Draw(DXGame *, Camera *); // Vẽ Object theo camera
	virtual void Draw(DXGame *, Camera *, D3DXCOLOR); 
	virtual void UpdateBound();
	virtual Box GetObjectBox();
	virtual EObjectName GetType();
	virtual ~BaseObject();
};

#endif