#include "TextureManagement.h"

#include"CastlePlayer.h"

TextureManagement TextureManagement::_instance = TextureManagement();

bool TextureManagement::Add(LPDIRECT3DDEVICE9 d3dDevice, EOTexture type, char *path)
{
	if (_ListTexture.find(type) != _ListTexture.end()) // đã tồn tại
		return false;

	DXTexture *texture = new DXTexture(d3dDevice);
	texture->LoadTexture(path);
	_ListTexture[type] = texture;

	return true;
}

bool TextureManagement::Add(LPDIRECT3DDEVICE9 d3dDevice, EOTexture type, char *path, int nHor, int nVer)
{
	if (_ListTexture.find(type) != _ListTexture.end()) // đã tồn tại
		return false;

	DXTexture *texture = new DXTexture(d3dDevice);
	texture->LoadTexture(path, nHor, nVer);
	_ListTexture[type] = texture;

	return true;
}

void TextureManagement::AddAll(LPDIRECT3DDEVICE9 d3dDevice)
{	
	this->Add(d3dDevice, EOTexture::BACKGROUND_TEXTURE, "BeginBackground.png", SCREEN_WIDTH / OBJECT_WIDTH, SCREEN_HEIGHT / OBJECT_HEIGHT);
	this->Add(d3dDevice, EOTexture::BEGINBACKGROUND_TEXTURE, "BeginBackground.png", SCREEN_WIDTH / OBJECT_WIDTH, SCREEN_HEIGHT / OBJECT_HEIGHT);
	this->Add(d3dDevice, EOTexture::ABOUTBACKGROUND_TEXTURE, "AboutBackground.png", SCREEN_WIDTH / OBJECT_WIDTH, SCREEN_HEIGHT / OBJECT_HEIGHT);
	this->Add(d3dDevice, EOTexture::SETTINGBACKGROUND_TEXTURE, "SettingBackground.png", SCREEN_WIDTH / OBJECT_WIDTH, SCREEN_HEIGHT / OBJECT_HEIGHT);

	this->Add(d3dDevice, EOTexture::BRICK_TEXTURE, "gachnau2.png");	
	this->Add(d3dDevice, EOTexture::ENEMY_TEXTURE, "doi.png");
	this->Add(d3dDevice, EOTexture::EXPLOREDBRICK_TEXTURE, "ExploredBrick.png");

	this->Add(d3dDevice, EOTexture::FIREWORKS_TEXTURE, "Fireworks.png");
	this->Add(d3dDevice, EOTexture::FLAGPOLE_TEXTURE, "FlagPole.png");
	this->Add(d3dDevice, EOTexture::FLOWER_TEXTURE, "Flower.png");
	this->Add(d3dDevice, EOTexture::GAMEOVERSCREEN_TEXTURE, "GameOverScreen.png", SCREEN_WIDTH / OBJECT_WIDTH, SCREEN_HEIGHT / OBJECT_HEIGHT);

	this->Add(d3dDevice, EOTexture::HEIGHTMARIO_TEXTURE, "CastleSit.png");
	this->Add(d3dDevice, EOTexture::HORIZONTALPIPE_TEXTURE, "HorizontalPipe.png");
	this->Add(d3dDevice, EOTexture::LAMP_TEXTURE, "Lamp.png");
	this->Add(d3dDevice, EOTexture::LAND_TEXTURE, "gachnau.png");
	this->Add(d3dDevice, EOTexture::MACHINEBULLET_TEXTURE, "MachineBullet.png");
	this->Add(d3dDevice, EOTexture::MACHINE_TEXTURE, "Machine.png");
	this->Add(d3dDevice, EOTexture::MARIOICON_TEXTURE, "castleicon.png");

	this->Add(d3dDevice, EOTexture::MOUNTAIN_TEXTURE, "doi.png");
	this->Add(d3dDevice, EOTexture::MUSHROOM_TEXTURE, "Mushroom.png");
	this->Add(d3dDevice, EOTexture::NUMBER_TEXTURE, "Number.png", 10, 1);
	this->Add(d3dDevice, EOTexture::PAUSEMENU_TEXTURE, "PauseMenu.png");

	this->Add(d3dDevice, EOTexture::SECRETBLOCK_TEXTURE, "SecretBlock.png");
	this->Add(d3dDevice, EOTexture::SIGN_TEXTURE, "Sign.png");

	// Nhân vật load trong map begin
	this->Add(d3dDevice, EOTexture::SMALLMARIO_TEXTURE, "CastleWalk.png");

	this->Add(d3dDevice, EOTexture::SPRING_TEXTURE, "Spring.png");
	this->Add(d3dDevice, EOTexture::STAR_TEXTURE, "Star.png");

	this->Add(d3dDevice, EOTexture::STARTMENU_TEXTURE, "Menu.png");
	this->Add(d3dDevice, EOTexture::SUPERMATIO_TEXTURE, "CastleBullet.png");
	this->Add(d3dDevice, EOTexture::TOWER_TEXTURE, "Tower.png");
	this->Add(d3dDevice, EOTexture::TREE_TEXTURE, "Tree.png");
	this->Add(d3dDevice, EOTexture::TREE2_TEXTURE, "Tree2.png");

	this->Add(d3dDevice, EOTexture::TURTLE_TEXTURE, "0.png");
	this->Add(d3dDevice, EOTexture::TURTLE2_TEXTURE, "Turtle2.png");
	this->Add(d3dDevice, EOTexture::WAITSCREEN_TEXTURE, "WaitScreen.png", SCREEN_WIDTH / OBJECT_WIDTH, SCREEN_HEIGHT / OBJECT_HEIGHT);
	this->Add(d3dDevice, EOTexture::WORLD_TEXTURE, "World.png");

	this->Add(d3dDevice, EOTexture::BACKGROUND_BLUE_TEXTURE, "backgroundblue.png");
	this->Add(d3dDevice, EOTexture::CAUTHANG_TEXTURE, "cauthang.png");
	this->Add(d3dDevice, EOTexture::CANHCUA_TEXTURE, "cuadong.png");
	this->Add(d3dDevice, EOTexture::DAUTRU_TEXTURE, "dautru.png");
	this->Add(d3dDevice, EOTexture::GACHDEN_TEXTURE, "gachden.png");
	this->Add(d3dDevice, EOTexture::GACHDEN_TRAI_TEXTURE, "gachdentrai.png");
	this->Add(d3dDevice, EOTexture::GACHDO_TEXTURE, "gachdo.png");
	this->Add(d3dDevice, EOTexture::GACHDO_XAM_TEXTURE, "gachdoxam.png");
	this->Add(d3dDevice, EOTexture::GACHGIUA_DAUTRU_TEXTURE, "gachgiuadautru.png");
	this->Add(d3dDevice, EOTexture::NENGACH_TEXTURE, "nengach.png");
	this->Add(d3dDevice, EOTexture::NENGACH_TRAI_TEXTURE, "nengachtrai.png");
	this->Add(d3dDevice, EOTexture::NGONDUOC_TEXTURE, "ngonduoc.png");
	this->Add(d3dDevice, EOTexture::NGONNEN_TEXTURE, "ngonnen.png");
	this->Add(d3dDevice, EOTexture::THANHTRUOT_TEXTURE, "thanhtruot.png");
	this->Add(d3dDevice, EOTexture::TRU_TEXTURE, "tru.png");
	this->Add(d3dDevice, EOTexture::TRUTIM_1_TEXTURE, "trutim.png");
	this->Add(d3dDevice, EOTexture::TRUTIM_2_TEXTURE, "trutim2.png");
	this->Add(d3dDevice, EOTexture::TRUTIM_3_TEXTURE, "trutim3.png");

	this->Add(d3dDevice, EOTexture::BULLET_TEXTURE, "boomerang.png");


	//Enemy
	this->Add(d3dDevice, EOTexture::DOI_TEXTURE, "Enemy/doi.png");
	this->Add(d3dDevice, EOTexture::ECH_TEXTURE, "Enemy/9.png");
	this->Add(d3dDevice, EOTexture::CONMA_TEXTURE, "Enemy/1.png");
	this->Add(d3dDevice, EOTexture::BOSSMAP1_TEXTURE, "Enemy/boss1.png");
	this->Add(d3dDevice, EOTexture::BANCHONG_TEXTURE, "Enemy/banchong.png");
	this->Add(d3dDevice, EOTexture::CHO_TEXTURE, "Enemy/cho.png");
	this->Add(d3dDevice, EOTexture::DAULAU_TEXTURE, "Enemy/daulau.png");
	this->Add(d3dDevice, EOTexture::DAUQUAI_TEXTURE, "Enemy/dauquai.png");
	this->Add(d3dDevice, EOTexture::LINHCANH_TEXTURE, "Enemy/linhcanh.png");
	this->Add(d3dDevice, EOTexture::NGUOIECH_TEXTURE, "Enemy/nguoiech.png");

	//
	//Item
	this->Add(d3dDevice, EOTexture::BINHVANG_TEXTURE, "Item/binhvang.png");
	this->Add(d3dDevice, EOTexture::DAYCHUYEN_TEXTURE, "Item/daychuyen.png");
	this->Add(d3dDevice, EOTexture::DUIGA_TEXTURE, "Item/duiga.png");
	this->Add(d3dDevice, EOTexture::NUOCTHANH_TEXTURE, "Item/nuochanh.png");
	this->Add(d3dDevice, EOTexture::NGOC_TEXTURE, "Item/ngoc.png");
	this->Add(d3dDevice, EOTexture::RUONG_TEXTURE, "Item/ruong.png");
	this->Add(d3dDevice, EOTexture::TUITIENTRANG_TEXTURE, "Item/tuitientrang.png");
	this->Add(d3dDevice, EOTexture::TUITIENXANH_TEXTURE, "Item/tuitienxanh.png");
	this->Add(d3dDevice, EOTexture::TRAITIMLON_TEXTURE, "Item/traitimlon.png");
	this->Add(d3dDevice, EOTexture::TRAITIMNHO_TEXTURE, "Item/traitimnho.png");
	this->Add(d3dDevice, EOTexture::VUONGMIENG_TEXTURE, "Item/vuongmieng.png");

	//

}

DXTexture* TextureManagement::Get(EOTexture name)
{
	map<EOTexture, DXTexture *>::iterator i;
	i = _ListTexture.find(name);
	if (i == _ListTexture.end())
	{
		return NULL;
	}

	return i->second;
}

EOTexture TextureManagement::Get(DXTexture *texture)
{
	map<EOTexture, DXTexture *>::iterator i;
	for (i = _ListTexture.begin(); i != _ListTexture.end(); i++)
	{
		if (i->second == this->Get(i->first))
			return i->first;
	}

	return EOTexture::BACKGROUND_TEXTURE;
}

