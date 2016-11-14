#include "OtherObj.h"


Land::Land(DXTexture *pTexture, D3DXVECTOR2 position)
	:StaticObject(pTexture, position)
{
	this->_width = this->_texture->GetWidth() ;
	this->_height = this->_texture->GetHeight();	
	BaseObject::Update(NULL);
	
	this->_OType = EObjectName::GACHNAU_OBJECT;
}

CauThang::CauThang(DXTexture *pTexture, D3DXVECTOR2 position)
	:StaticObject(pTexture, position)
{
	this->_width = this->_texture->GetWidth() / 2;
	this->_height = this->_texture->GetHeight() / 2;
	BaseObject::Update(NULL);

	this->_OType = EObjectName::CAUTHANG_OBJECT;
}


Tower::Tower(DXTexture *pTexture, D3DXVECTOR2 position)
	:StaticObject(pTexture, position)
{
	this->_OType = EObjectName::TOWER_OBJECT;

	_rect.left = _position.x - _width / 4;
	_rect.right = _position.x + _width / 4;
	_rect.top = _position.y - _height / 4;
	_rect.bottom = _position.y - _height / 2;
}

Block::Block(DXTexture *ptexture, D3DXVECTOR2 position)
	:StaticObject(ptexture, position)
{
	
}


Scene::Scene(DXTexture *ptexture, D3DXVECTOR2 position, ESceneObject type)
	:StaticObject(ptexture, position)
{
	this->_rect.top = 0;
	this->_rect.left = 0;
	this->_rect.right = 0;
	this->_rect.bottom = 0;

	if (type == ESceneObject::BACKGROUNDBLUE)
	{
		this->_OType = EObjectName::BACKGROUND_BLUE_OBJECT;
	}
	else if (type == ESceneObject::DAUTRU)
	{
		this->_OType = EObjectName::DAUTRU_OBJECT;
	}
	else if (type == ESceneObject::GACHDEN)
	{
		this->_OType = EObjectName::GACHDEN_OBJECT;
	}
	else if (type == ESceneObject::GACHDEN_TRAI)
	{
		this->_OType = EObjectName::GACHDEN_TRAI_OBJECT;
	}
	else if (type == ESceneObject::GACHDO)
	{
		this->_OType = EObjectName::GACHDO_OBJECT;
	}
	else if (type == ESceneObject::GACHDO_XAM)
	{
		this->_OType = EObjectName::GACHDO_XAM_OBJECT;
	}
	else if (type == ESceneObject::GACHDO_XAM)
	{
		this->_OType = EObjectName::GACHDO_XAM_OBJECT;
	}
	else if (type == ESceneObject::GACHGIUA_DAUTRU)
	{
		this->_OType = EObjectName::GACHGIUA_DAUTRU_OBJECT;
	}
	else if (type == ESceneObject::NENGACH)
	{
		this->_OType = EObjectName::NENGACH_OBJECT;
	}
	else if (type == ESceneObject::NENGACH_TRAI)
	{
		this->_OType = EObjectName::NENGACH_TRAI_OBJECT;
	}
	else if (type == ESceneObject::TRU)
	{
		this->_OType = EObjectName::TRU_OBJECT;
	}
	else if (type == ESceneObject::TRUTIM_1)
	{
		this->_OType = EObjectName::TRUTIM_1_OBJECT;
	}
	else if (type == ESceneObject::TRUTIM_2)
	{
		this->_OType = EObjectName::TRUTIM_2_OBJECT;
	}
	else if (type == ESceneObject::TRUTIM_3)
	{
		this->_OType = EObjectName::TRUTIM_3_OBJECT;
	}
}