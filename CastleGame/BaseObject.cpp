#include "BaseObject.h"


BaseObject::BaseObject(DXTexture *tex, D3DXVECTOR2 pos)
{
	this->_OType = EObjectName::NONE_OBJECT;

	this->_texture = tex;
	this->_position = pos;
	this->_offset_X = 0;
	this->_offset_Y = 0;

	// mặc định nếu không set
	if (this->_texture != NULL)
	{
		this->_width = _texture->GetWidth(); 
		this->_height = _texture->GetHeight();
	}
	else
	{
		this->_width = 0;
		this->_height = 0;
	}

	this->UpdateBound();
}

void BaseObject::Update(GameTime *gameTime)
{
	this->UpdateBound();
}

void BaseObject::Draw(DXGame *pDXGame, Camera *pCamera)
{
	// xác định rect cắt frame animation
	_rectSource.left = _offset_X * _width;
	_rectSource.right = _rectSource.left + _width;
	_rectSource.top = _offset_Y * _height;
	_rectSource.bottom = _rectSource.top + _height;

	D3DXVECTOR4 tmpOut; // Lưu tọa độ của object sau khi transform
	D3DXVECTOR2 centerPos;
	
	/*
	centerPos = D3DXVECTOR2(_position.x + _width / 2, _position.y + _height / 2); // tính tọa độ trung tâm hiện tại
	D3DXVec2Transform(&tmpOut, &centerPos, &pCamera->_matrix); // transform
	centerPos = D3DXVECTOR2(tmpOut.x, tmpOut.y); // tính tọa độ trung tâm sau khi transform
	*/
	D3DXVec2Transform(&tmpOut, &_position, &pCamera->_matrix); // transform
	centerPos = D3DXVECTOR2(tmpOut.x, tmpOut.y); // tính tọa độ trung tâm sau khi transform

	pDXGame->DrawTexture(_texture, &centerPos, _width, _height, &_rectSource);
}

void BaseObject::Draw(DXGame *pDXGame, Camera *pCamera, D3DXCOLOR color)
{
	// xác định rect cắt frame animation
	_rectSource.left = _offset_X * _width;
	_rectSource.right = _rectSource.left + _width;
	_rectSource.top = _offset_Y * _height;
	_rectSource.bottom = _rectSource.top + _height;

	D3DXVECTOR4 tmpOut; // Lưu tọa độ của object sau khi transform
	D3DXVECTOR2 centerPos;
	
	/*
	centerPos = D3DXVECTOR2(_position.x + _width / 2, _position.y + _height / 2); // tính tọa độ trung tâm hiện tại
	D3DXVec2Transform(&tmpOut, &centerPos, &pCamera->_matrix); // transform
	centerPos = D3DXVECTOR2(tmpOut.x, tmpOut.y); // tính tọa độ trung tâm sau khi transform
	*/
	D3DXVec2Transform(&tmpOut, &_position, &pCamera->_matrix); // transform
	centerPos = D3DXVECTOR2(tmpOut.x, tmpOut.y); // tính tọa độ trung tâm sau khi transform

	pDXGame->DrawTexture(_texture, &centerPos, _width, _height, &_rectSource, color);
}

void BaseObject::UpdateBound()
{
	// cập nhật hình chữ nhật bao quanh đối tượng
	_rect.left = _position.x - _width / 2 + 1;
	_rect.right = _rect.left + _width - 2;
	_rect.top = _position.y + _height / 2 - 1;
	_rect.bottom = _rect.top - _height + 2;
}

Box BaseObject::GetObjectBox()
{
	return ConvertRectToBox(_rect);
}

EObjectName BaseObject::GetType()
{
	return this->_OType;
}

BaseObject::~BaseObject()
{
}