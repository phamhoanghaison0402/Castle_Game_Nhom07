#ifndef _BUILD_H_
#define _BUILD_H_


#include "TextureManagement.h"

#include "Map.h"
#include "QuadTree.h"
#include "CastlePlayer.h"
#include "Enemy.h"
#include "Brick.h"
#include "OtherObj.h"
#include"CanhCua.h"
#include"NgonDuoc.h"
#include"NgonNen.h"
#include"ThanhTruot.h"

//Enemy
#include "Doi.h"
#include "Ech.h"
#include "ConMa.h"
#include "BossMap1.h"
#include "BanChong.h"
#include "LinhCanh.h"
#include "NguoiEch.h"
#include "DauQuai.h"
#include "DauLau.h"
#include "Cho.h"

//Item
#include "BinhVang.h"
#include "DayChuyen.h"
#include "NuocThanh.h"
#include "Ngoc.h"
#include "TuiTienTrang.h"
#include "TuiTienXanh.h"
#include "TraiTimLon.h"
#include "TraiTimNho.h"
#include "Ruong.h"
#include "VuongMieng.h"
#include "DuiGa.h"

enum EQuadTreeType
{
	DRAW,
	UPDATE
};


static BaseObject* MakeObject(EObjectName type, D3DXVECTOR2 pos)
{
	TextureManagement *tm = TextureManagement::GetInstance();
	BaseObject *obj = NULL;
	switch (type)
	{
		// enemy
	case EObjectName::BOSS_1_OBJECT:
		obj = new Enemy(tm->Get(EOTexture::ENEMY_TEXTURE), pos);
		break;
	
	/*case EObjectName::BRICK_OBJECT:
		obj = new Brick(tm->Get(EOTexture::BRICK_TEXTURE), tm->Get(EOTexture::EXPLOREDBRICK_TEXTURE), pos, tm->Get(EOTexture::COIN_TEXTURE), false);
		break;*/
	/*case EObjectName::LEFT_LAND_OBJECT:
		obj = new Land(tm->Get(EOTexture::LAND_TEXTURE), pos, TypeOfLand::LEFT_LAND);
		break;*/
	case EObjectName::GACHNAU_OBJECT:
		obj = new Land(tm->Get(EOTexture::LAND_TEXTURE), pos);
		break;

	case EObjectName::NGONDUOC_OBJECT:
		obj = new NgonDuoc(tm->Get(EOTexture::NGONDUOC_TEXTURE), pos);
		break;

	case EObjectName::NGONNEN_OBJECT:
		obj = new NgonNen(tm->Get(EOTexture::NGONNEN_TEXTURE), pos);
		break;

	case EObjectName::CAUTHANG_OBJECT:
		obj = new CauThang(tm->Get(EOTexture::CAUTHANG_TEXTURE), pos);
		break;
	case EObjectName::THANHTRUOT_OBJECT:
		obj = new ThanhTruot(tm->Get(EOTexture::THANHTRUOT_TEXTURE), pos);
		break;

	/*case EObjectName::RIGHT_LAND_OBJECT:
		obj = new Land(tm->Get(EOTexture::LAND_TEXTURE), pos, TypeOfLand::RIGHT_LAND);
		break;*/
			
	case EObjectName::DAUTRU_OBJECT:
		obj = new Scene(tm->Get(EOTexture::DAUTRU_TEXTURE), pos, ESceneObject::DAUTRU);
		break;

	case EObjectName::TRU_OBJECT:
		obj = new Scene(tm->Get(EOTexture::TRU_TEXTURE), pos, ESceneObject::TRU);
		break;

	case EObjectName::TOWER_OBJECT:
		obj = new Tower(tm->Get(EOTexture::TOWER_TEXTURE), pos);
		break;

	case EObjectName::BACKGROUND_BLUE_OBJECT:
		obj = new Scene(tm->Get(EOTexture::BACKGROUND_BLUE_TEXTURE), pos, ESceneObject::BACKGROUNDBLUE);
		break;
	case EObjectName::GACHDEN_OBJECT:
		obj = new Scene(tm->Get(EOTexture::GACHDEN_TEXTURE), pos, ESceneObject::GACHDEN);
		break;
	case EObjectName::GACHDEN_TRAI_OBJECT:
		obj = new Scene(tm->Get(EOTexture::GACHDEN_TRAI_TEXTURE), pos, ESceneObject::GACHDEN_TRAI);
		break;
	case EObjectName::GACHDO_OBJECT:
		obj = new Scene(tm->Get(EOTexture::GACHDO_TEXTURE), pos, ESceneObject::GACHDO);
		break;
	case EObjectName::GACHDO_XAM_OBJECT:
		obj = new Scene(tm->Get(EOTexture::GACHDO_XAM_TEXTURE), pos, ESceneObject::GACHDO_XAM);
		break;
	case EObjectName::GACHGIUA_DAUTRU_OBJECT:
		obj = new Scene(tm->Get(EOTexture::GACHGIUA_DAUTRU_TEXTURE), pos, ESceneObject::GACHGIUA_DAUTRU);
		break;
	case EObjectName::NENGACH_OBJECT:
		obj = new Scene(tm->Get(EOTexture::NENGACH_TEXTURE), pos, ESceneObject::NENGACH);
		break;
	case EObjectName::NENGACH_TRAI_OBJECT:
		obj = new Scene(tm->Get(EOTexture::NENGACH_TRAI_TEXTURE), pos, ESceneObject::NENGACH_TRAI);
		break;
	case EObjectName::TRUTIM_1_OBJECT:
		obj = new Scene(tm->Get(EOTexture::TRUTIM_1_TEXTURE), pos, ESceneObject::TRUTIM_1);
		break;
	case EObjectName::TRUTIM_2_OBJECT:
		obj = new Scene(tm->Get(EOTexture::TRUTIM_2_TEXTURE), pos, ESceneObject::TRUTIM_2);
		break;
	case EObjectName::TRUTIM_3_OBJECT:
		obj = new Scene(tm->Get(EOTexture::TRUTIM_3_TEXTURE), pos, ESceneObject::TRUTIM_3);
		break;

		
	default:
		break;
	}

	return obj;
}

// khởi tạo các đối tượng
static map<int, BaseObject *>* BuildObjectsMap(Map *m, CastlePlayer *&mario, map<int, D3DXVECTOR2 *> &creepPos, list<D3DXVECTOR2 *> &flagPos)
{
	TextureManagement *tm = TextureManagement::GetInstance();
	map<int, BaseObject *> *listObjects = new map<int, BaseObject *>();

	// khởi tạo các đối tượng, đưa vào list
	for (list<GameObject *>::iterator i = m->GetGameObjects().begin(); i != m->GetGameObjects().end(); i++)
	{
		BaseObject *obj = NULL;
		D3DXVECTOR2 pos;

		pos = D3DXVECTOR2((*i)->GetX(), (*i)->GetY());

		switch ((EObjectName)(*i)->GetType())
		{
			// enemy
		case EObjectName::BOSS_1_OBJECT:
			obj = new Enemy(tm->Get(EOTexture::ENEMY_TEXTURE), pos);
			break;

		/*
		case EObjectName::BRICK_OBJECT:
			obj = new Brick(tm->Get(EOTexture::BRICK_TEXTURE), tm->Get(EOTexture::EXPLOREDBRICK_TEXTURE), pos, tm->Get(EOTexture::COIN_TEXTURE), false);
			break;*/
				
		/*case EObjectName::LEFT_LAND_OBJECT:
			obj = new Land(tm->Get(EOTexture::LAND_TEXTURE), pos, TypeOfLand::LEFT_LAND);
			break;*/
		case EObjectName::GACHNAU_OBJECT:
			obj = new Land(tm->Get(EOTexture::LAND_TEXTURE), pos);
			break;
		case EObjectName::CAUTHANG_OBJECT:
			obj = new CauThang(tm->Get(EOTexture::CAUTHANG_TEXTURE), pos);
			break;
		case EObjectName::CANHCUA_OBJECT:
			obj = new CanhCua(tm->Get(EOTexture::CANHCUA_TEXTURE), pos);
			break;

		case EObjectName::NGONDUOC_OBJECT:
			obj = new NgonDuoc(tm->Get(EOTexture::NGONDUOC_TEXTURE), pos);
			break;
		case EObjectName::NGONNEN_OBJECT:
			obj = new NgonNen(tm->Get(EOTexture::NGONNEN_TEXTURE), pos);
			break;
		case EObjectName::THANHTRUOT_OBJECT:
			obj = new ThanhTruot(tm->Get(EOTexture::THANHTRUOT_TEXTURE), pos);
			break;

		/*case EObjectName::RIGHT_LAND_OBJECT:
			obj = new Land(tm->Get(EOTexture::LAND_TEXTURE), pos, TypeOfLand::RIGHT_LAND);
			break;*/

		case EObjectName::DAUTRU_OBJECT:
			obj = new Scene(tm->Get(EOTexture::DAUTRU_TEXTURE), pos, ESceneObject::DAUTRU);
			break;
		case EObjectName::GACHDEN_OBJECT:
			obj = new Scene(tm->Get(EOTexture::GACHDEN_TEXTURE), pos, ESceneObject::GACHDEN);
			break;
		case EObjectName::GACHDEN_TRAI_OBJECT:
			obj = new Scene(tm->Get(EOTexture::GACHDEN_TRAI_TEXTURE), pos, ESceneObject::GACHDEN_TRAI);
			break;
		case EObjectName::GACHDO_OBJECT:
			obj = new Scene(tm->Get(EOTexture::GACHDO_TEXTURE), pos, ESceneObject::GACHDO);
			break;
		case EObjectName::GACHDO_XAM_OBJECT:
			obj = new Scene(tm->Get(EOTexture::GACHDO_XAM_TEXTURE), pos, ESceneObject::GACHDO_XAM);
			break;
		case EObjectName::GACHGIUA_DAUTRU_OBJECT:
			obj = new Scene(tm->Get(EOTexture::GACHGIUA_DAUTRU_TEXTURE), pos, ESceneObject::GACHGIUA_DAUTRU);
			break;
		case EObjectName::NENGACH_OBJECT:
			obj = new Scene(tm->Get(EOTexture::NENGACH_TEXTURE), pos, ESceneObject::NENGACH);
			break;	
		case EObjectName::NENGACH_TRAI_OBJECT:
			obj = new Scene(tm->Get(EOTexture::NENGACH_TRAI_TEXTURE), pos, ESceneObject::FENCE);
			break;	
		case EObjectName::TRU_OBJECT:
			obj = new Scene(tm->Get(EOTexture::TRU_TEXTURE), pos, ESceneObject::TRU);
			break;
		case EObjectName::TRUTIM_1_OBJECT:
			obj = new Scene(tm->Get(EOTexture::TRUTIM_1_TEXTURE), pos, ESceneObject::TRUTIM_1);
			break;
		case EObjectName::TRUTIM_2_OBJECT:
			obj = new Scene(tm->Get(EOTexture::TRUTIM_2_TEXTURE), pos, ESceneObject::TRUTIM_2);
			break;
		case EObjectName::TRUTIM_3_OBJECT:
			obj = new Scene(tm->Get(EOTexture::TRUTIM_3_TEXTURE), pos, ESceneObject::TRUTIM_3);
			break;

		case EObjectName::BACKGROUND_BLUE_OBJECT:
			obj = new Scene(tm->Get(EOTexture::BACKGROUND_BLUE_TEXTURE), pos, ESceneObject::BACKGROUNDBLUE);
			break;

		case EObjectName::TOWER_OBJECT:
			obj = new Tower(tm->Get(EOTexture::TOWER_TEXTURE), pos);
			break;

			//Enemy
		case EObjectName::DOI_OBJECT:
			obj = new Doi(tm->Get(EOTexture::DOI_TEXTURE), pos);
			break;

			/*case EObjectName::BOSS_1_OBJECT:
			obj = new BossMap1(tm->Get(EOTexture::BOSSMAP1_TEXTURE), pos);
			break;*/

		case EObjectName::MA_OBJECT:
			obj = new Ma(tm->Get(EOTexture::CONMA_TEXTURE), pos);
			break;

		case EObjectName::ECH_OBJECT:
			obj = new Ech(tm->Get(EOTexture::ECH_TEXTURE), pos);
			break;

		case EObjectName::CHO_OBJECT:
			obj = new Cho(tm->Get(EOTexture::CHO_TEXTURE), pos);
			break;

		case EObjectName::DAULAU_OBJECT:
			obj = new DauLau(tm->Get(EOTexture::DAULAU_TEXTURE), pos);
			break;

		case EObjectName::DAUQUAI_OBJECT:
			obj = new DauQuai(tm->Get(EOTexture::DAUQUAI_TEXTURE), pos);
			break;

		case EObjectName::LINHCANH_OBJECT:
			obj = new LinhCanh(tm->Get(EOTexture::LINHCANH_TEXTURE), pos);
			break;

		case EObjectName::NGUOIECH_OBJECT:
			obj = new NguoiEch(tm->Get(EOTexture::NGUOIECH_TEXTURE), pos);
			break;

		case EObjectName::BANCHONG_OBJECT:
			obj = new BanChong(tm->Get(EOTexture::BANCHONG_TEXTURE), pos);
			break;
			//

			//Item
		case EObjectName::BINHVANG_OBJECT:
			obj = new BinhVang(tm->Get(EOTexture::BINHVANG_TEXTURE), pos);
			break;

		case EObjectName::DAYCHUYEN_OBJECT:
			obj = new DayChuyen(tm->Get(EOTexture::DAYCHUYEN_TEXTURE), pos);
			break;

		case EObjectName::NUOCTHANH_OBJECT:
			obj = new NuocThanh(tm->Get(EOTexture::NUOCTHANH_TEXTURE), pos);
			break;

		case EObjectName::RUONG_OBJECT:
			obj = new Ruong(tm->Get(EOTexture::RUONG_TEXTURE), pos);
			break;

		case EObjectName::NGOC_OBJECT:
			obj = new Ngoc(tm->Get(EOTexture::NGOC_TEXTURE), pos);
			break;

		case EObjectName::TUITIEN_TRANG_OBJECT:
			obj = new TuiTienTrang(tm->Get(EOTexture::TUITIENTRANG_TEXTURE), pos);
			break;

		case EObjectName::TUITIEN_XANH_OBJECT:
			obj = new TuiTienXanh(tm->Get(EOTexture::TUITIENXANH_TEXTURE), pos);
			break;

		case EObjectName::TRAITIM_LON_OBJECT:
			obj = new TraiTimLon(tm->Get(EOTexture::TRAITIMLON_TEXTURE), pos);
			break;

		case EObjectName::TRAITIM_NHO_OBJECT:
			obj = new TraiTimNho(tm->Get(EOTexture::TRAITIMNHO_TEXTURE), pos);
			break;

		case EObjectName::VUONGMIENG_OBJECT:
			obj = new VuongMieng(tm->Get(EOTexture::VUONGMIENG_TEXTURE), pos);
			break;

		case EObjectName::DUIGA_OBJECT:
			obj = new DuiGa(tm->Get(EOTexture::DUIGA_TEXTURE), pos);
			break;
			//

		case EObjectName::MARIO_OBJECT:
			if (mario == NULL)
			{
				mario = new CastlePlayer(
					tm->Get(EOTexture::SMALLMARIO_TEXTURE),
					tm->Get(EOTexture::HEIGHTMARIO_TEXTURE),
					tm->Get(EOTexture::SUPERMATIO_TEXTURE),
					tm->Get(EOTexture::BULLET_TEXTURE),
					pos,
					CastleType::CASTLE_WALK);
			}
			break;
		default:
			break;
		}

		if (obj != NULL)
		{
			pair<int, BaseObject *> p((*i)->GetID(), obj);
			listObjects->insert(p);
		}
	}

	return listObjects;
}

// khởi tạo các qnode
static map<int, QNode *>* BuildQNodesMap(Map *m, map<int, BaseObject *> *listObjects, EQuadTreeType type)
{
	map<int, QNode *> *qNodes = new map<int, QNode *>();
	list<Node *> listNodes;
	if (type == EQuadTreeType::DRAW)
	{
		listNodes = m->GetNodes();
	}
	else if (type == EQuadTreeType::UPDATE)
	{
		listNodes = m->GetUpdateNodes();
	}

	RECT *rect;
	list<BaseObject *> *objectsInNode;
	BaseObject *bo;
	QNode *subNode = NULL;
	for (list<Node *>::iterator iNode = listNodes.begin(); iNode != listNodes.end(); iNode++)
	{
		// HCN bound
		rect = new RECT();
		rect->left = (*iNode)->GetX();
		rect->right = rect->left + (*iNode)->GetWidth();
		rect->top = (*iNode)->GetY();
		rect->bottom = rect->top - (*iNode)->GetHeight();

		// tham chiếu tới list các đối tượng trong node
		objectsInNode = new list<BaseObject *>();
		list<GameObject *>::iterator iObject;
		list<GameObject *> list = (*iNode)->GetGameObjects();
		for (iObject = (*iNode)->GetGameObjects().begin(); iObject != (*iNode)->GetGameObjects().end(); iObject++)
		{
			for (map<int, BaseObject *>::iterator iRealObject = listObjects->begin(); iRealObject != listObjects->end(); iRealObject++)
			{
				if ((*iObject)->GetID() == iRealObject->first)
				{
					objectsInNode->push_back(iRealObject->second);
				}
			}
		}

		subNode = new QNode((*iNode)->GetID(), *rect);
		subNode->InsertObjects(objectsInNode);
		qNodes->insert(pair<int, QNode *>(subNode->GetID(), subNode));
	}

	return qNodes;
}

// xây dựng cây
static QuadTree* BuildQuadTree(map<int, QNode *> *listQNode)
{
	QuadTree *quadTree;

	map<int, QNode *>::iterator iQNode;
	QNode *root;
	QNode* q;
	iQNode = listQNode->begin();
	root = iQNode->second;
	for (iQNode++; iQNode != listQNode->end(); iQNode++)
	{
		int parentID = iQNode->second->GetParentID();
		q = listQNode->at(parentID);
		q->AddChildNode(iQNode->second);
	}

	quadTree = new QuadTree(root);
	return quadTree;
}

static QuadTree* BuildQuadTree(Map *m, map<int, BaseObject *> *listObjects, EQuadTreeType type, map<int, QNode *> *&qNodes)
{
	qNodes = BuildQNodesMap(m, listObjects, type);
	return BuildQuadTree(qNodes);
}

static bool RemoveDeadObjects(map<int, BaseObject *> &_listObjects, QuadTree *_quadTree, QuadTree *_updateQuadTree, BaseObject *obj)
{
	map<int, BaseObject *>::iterator iter;
	for (iter = _listObjects.begin(); iter != _listObjects.end(); iter++)
	{
		if (iter->second == obj)
			break;
	}

	if (iter == _listObjects.end())
		return false;

	switch (iter->second->GetType())
	{
	
	case EObjectName::BULLET_OBJECT:
		if ( ((DynamicObject *)iter->second)->_isDead == true )
		{
			_quadTree->RemoveObj(iter->second, _quadTree->GetRootNode());
			_updateQuadTree->RemoveObj(iter->second, _updateQuadTree->GetRootNode());
			delete iter->second;
			iter = _listObjects.erase(iter);
			return true;
		}
		break;

	case EObjectName::BOSS_1_OBJECT:
	case EObjectName::BANCHONG_OBJECT:
		if ( ((Enemy *)iter->second)->_isDisappear == true )
		{
			_quadTree->RemoveObj(iter->second, _quadTree->GetRootNode());
			_updateQuadTree->RemoveObj(iter->second, _updateQuadTree->GetRootNode());
 			delete iter->second;
			iter = _listObjects.erase(iter);
			return true;
		}
		break;

	/*case EObjectName::BRICK_OBJECT:
		if ( ((Brick *)iter->second)->_isDisappear == true )
		{
			_quadTree->RemoveObj(iter->second, _quadTree->GetRootNode());
			_updateQuadTree->RemoveObj(iter->second, _updateQuadTree->GetRootNode());
			delete iter->second;
			iter = _listObjects.erase(iter);
			return true;
		}
		break;*/

	default:
		break;
	}

	return false;
}

#endif