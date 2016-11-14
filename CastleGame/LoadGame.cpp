#include "LoadGame.h"


BaseObject* BObject::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();
	
	int ID, type, X, Y;
	Direction dir = NONE;
	bool isExplored, isCollision, hasSubObject;

	ID = atoi(xml.GetAttrib("ID").c_str());
	type = atoi(xml.GetAttrib("Type").c_str());
	X = atoi(xml.GetAttrib("X").c_str());
	Y = atoi(xml.GetAttrib("Y").c_str());

	dir = (Direction)atoi(xml.GetAttrib("dir").c_str());
	isExplored = (bool)atoi(xml.GetAttrib("isExplored").c_str());
	isCollision = (bool)atoi(xml.GetAttrib("isCollision").c_str());
	hasSubObject = (bool)atoi(xml.GetAttrib("hasSubObject").c_str());

	if (GListObjects[ID] == NULL)
	{
		BaseObject *obj;
		obj = MakeObject(EObjectName(type), D3DXVECTOR2(X,Y));

		switch (obj->GetType())
		{
		/*case EObjectName::BRICK_OBJECT:
			((Brick *)obj)->_isExplored = isExplored;
			if (isExplored)
			{
				((Brick *)obj)->_isDisappear = true;
			}
			if (hasSubObject == false)
			{
				((Brick *)obj)->_coin = NULL;
			}
			break;*/

		case EObjectName::BOSS_1_OBJECT:
			((Enemy *)obj)->_direction = dir;
			((Enemy *)obj)->_isCollisionWithMario = isCollision;
			if (isCollision == true)
			{
				((Enemy *)obj)->_isDead = true;
				((Enemy *)obj)->_isDisappear = true;
			}
			break;
		case EObjectName::BANCHONG_OBJECT:
			((Enemy *)obj)->_direction = dir;
			((Enemy *)obj)->_isCollisionWithMario = isCollision;
			break;

		

		default:
			break;
		};

		GListObjects[ID] = obj;
	}

	return GListObjects[ID];
}


void BObjects::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();
	if (xml.GetElemContent() != "")
	{
		xml.IntoElem();
		BObject *BObj;
		while (xml.FindElem("GameObject"))
		{
			BObj = new BObject();
			BaseObject *obj;
			obj = BObj->Deserialize(xml.GetSubDoc().c_str());
			_ListObjects.push_back(obj);
		}
	}
}

list<BaseObject *> & BObjects::GetListObjects()
{
	return this->_ListObjects;
}


Info & BInfo::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();

	_Info.IsSubWorld = (bool)atoi(xml.GetAttrib("IsSubWorld").c_str());
	_Info.nWorld = atoi(xml.GetAttrib("nWorld").c_str());

	_Info.SubWorld1 = xml.GetAttrib("SubWorld1").c_str();
	_Info.SubWorld1 = xml.GetAttrib("SubWorld2").c_str();

	_Info.CreepUpPos1 = D3DXVECTOR2(
		atoi(xml.GetAttrib("CreepUpPos1_X").c_str()),
		atoi(xml.GetAttrib("CreepUpPos1_Y").c_str())
		);
	_Info.CreepUpPos2 = D3DXVECTOR2(
		atoi(xml.GetAttrib("CreepUpPos2_X").c_str()),
		atoi(xml.GetAttrib("CreepUpPos2_Y").c_str())
		);

	_Info.TheNextWorld = xml.GetAttrib("TheNextWorld").c_str();

	_Info.OriMarioPos = D3DXVECTOR2(
		atoi(xml.GetAttrib("OriMarioPos_X").c_str()),
		atoi(xml.GetAttrib("OriMarioPos_Y").c_str())
		);

	_Info.Score = atoi(xml.GetAttrib("Score").c_str());
	_Info.Life = atoi(xml.GetAttrib("Life").c_str());
	_Info.World = atoi(xml.GetAttrib("World").c_str());

	return _Info;
}

Info & BInfo::GetInfo()
{
	return this->_Info;
}


CastlePlayer* BMario::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();

	int type, X, Y;
	bool SMoveLeft, SMoveRight, SJump, SFall, SDie;
	bool IsImmortality, EatMushroom, EatFlower, IsSmaller;

	type = atoi(xml.GetAttrib("Type").c_str());
	X = atoi(xml.GetAttrib("X").c_str());
	Y = atoi(xml.GetAttrib("Y").c_str());

	SMoveLeft = (bool)atoi(xml.GetAttrib("SMoveLeft").c_str());
	SMoveRight = (bool)atoi(xml.GetAttrib("SMoveRight").c_str());
	SJump = (bool)atoi(xml.GetAttrib("SJump").c_str());
	SFall = (bool)atoi(xml.GetAttrib("SFall").c_str());
	SDie = (bool)atoi(xml.GetAttrib("SDie").c_str());

	IsImmortality = (bool)atoi(xml.GetAttrib("IsImmortality").c_str());
	EatMushroom = (bool)atoi(xml.GetAttrib("EatMushroom").c_str());
	EatFlower = (bool)atoi(xml.GetAttrib("EatFlower").c_str());
	IsSmaller = (bool)atoi(xml.GetAttrib("IsSmaller").c_str());
	

	TextureManagement *tm = TextureManagement::GetInstance();
	CastlePlayer *mario = new CastlePlayer(
		tm->Get(EOTexture::SMALLMARIO_TEXTURE),
		tm->Get(EOTexture::HEIGHTMARIO_TEXTURE),
		tm->Get(EOTexture::SUPERMATIO_TEXTURE),
		tm->Get(EOTexture::BULLET_TEXTURE),
		D3DXVECTOR2(X, Y),
		CastleType(type));

	mario->_SMoveLeft = SMoveLeft;
	mario->_SMoveRight = SMoveRight;
	mario->_SJump = SJump;
	mario->_SFall = SFall;
	mario->_SDie = SDie;

	mario->_IsImmortality = IsImmortality;
	mario->_EatMushroom = EatMushroom;
	mario->_EatFlower = EatFlower;
	mario->_IsSmaller = IsSmaller;

	return mario;
}


pair<int, QNode *> & BQNode::Deserialize(const char *noidungcon)
{
	pair<int, QNode *> *p;
	int h, w, X, Y, ID;
	RECT r;

	CMarkup xml(noidungcon);
	xml.FindElem();

	h = atoi(xml.GetAttrib("Height").c_str());
	w = atoi(xml.GetAttrib("Width").c_str());
	X = atoi(xml.GetAttrib("X").c_str());
	Y = atoi(xml.GetAttrib("Y").c_str());
	ID = atoi(xml.GetAttrib("ID").c_str());
	xml.IntoElem();

	r.left = X;
	r.right = X + w;
	r.top = Y;
	r.bottom = r.top - h;

	if (xml.FindElem("GameObjects"))
	{
		BObjects *BObjs = new BObjects();
		BObjs->Deserialize(xml.GetSubDoc().c_str());
		_ListObjects = BObjs->GetListObjects();
	}

	QNode* q = new QNode(ID, r);
	q->InsertObjects(&_ListObjects);

	p = new pair<int, QNode *>(ID, q);
	return *p;
}

list<BaseObject *>& BQNode::GetListObjects()
{
	return this->_ListObjects;
}


void BQNodes::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();
	xml.IntoElem();

	while (xml.FindElem("Node"))
	{
		BQNode *bQNode = new BQNode();
		pair<int, QNode *> *node =  &bQNode->Deserialize(xml.GetSubDoc().c_str());
		_ListQNodes.insert(*node);
	}
}

map<int, QNode *> & BQNodes::GetListNodes()
{
	return this->_ListQNodes;
}

list<QNode *> & BQNodes::GetNodes()
{
	list<QNode *> *l = new list<QNode *>();
	for (map<int, QNode *>::iterator i = _ListQNodes.begin(); i != _ListQNodes.end(); i++)
	{
		l->push_back(i->second);
	}

	return *l;
}


void BSaveData::Deserialize(const char *tenfile)
{
	CMarkup xml;
	xml.Load(tenfile);
	xml.FindElem();
	xml.IntoElem();
	while (xml.FindElem())
	{
		if (xml.GetTagName() == "Width")
		{
			this->_Width = atoi(xml.GetData().c_str());
		}

		if (xml.FindElem("Height"))
		{
			this->_Height = atoi(xml.GetData().c_str());
		}

		if (xml.FindElem("GameInfo"))
		{
			BInfo *bInfo = new BInfo();
			_Info = &bInfo->Deserialize(xml.GetSubDoc().c_str());
		}

		if (xml.FindElem("Mario"))
		{
			BMario *bMario = new BMario();
			_Mario = bMario->Deserialize(xml.GetSubDoc().c_str());
		}

		if (xml.FindElem("Nodes"))
		{
			_Nodes.Deserialize(xml.GetSubDoc().c_str());
			_ListQNodes = _Nodes.GetListNodes();
			_ListObjects = GListObjects;
		}
	}
}

Info* BSaveData::GetInfo()
{
	return this->_Info;
}

CastlePlayer* BSaveData::GetCastlePlayer()
{
	return this->_Mario;
}

map<int, QNode *> & BSaveData::GetListQNodes()
{
	return this->_ListQNodes;
}

map<int, BaseObject *> & BSaveData::GetListObjects()
{
	return this->_ListObjects;
}


LoadGame::LoadGame(const char *filename)
{
	GListObjects.clear();
	char file[300];
	char tmpFilename[50];
	
	// Draw
	strcpy(tmpFilename, filename);
	strcat(tmpFilename, ".xml");

	GetCurrentDirectoryA(sizeof(file), file);
	file[sizeof(file) - 1] = '\0';
	strcat(file, "\\");
	strcat(file, tmpFilename);

	ifstream f(file);
	if (f.good() == false)
	{
		_hasData = false;
		return;
	}

	_data.Deserialize(file);
	_quadTree = BuildQuadTree(&_data.GetListQNodes());
	_ListObjects = _data.GetListObjects();
	_ListQNodes = _data.GetListQNodes();
	_Mario = _data.GetCastlePlayer();
	_Info = _data.GetInfo();

	// Update
	strcpy(tmpFilename, filename);
	strcat(tmpFilename, "Update.xml");

	GetCurrentDirectoryA(sizeof(file), file);
	file[sizeof(file) - 1] = '\0';
	strcat(file, "\\");
	strcat(file, tmpFilename);

	if (f.good() == false)
	{
		_hasData = false;
		return;
	}

	_updateData.Deserialize(file);
	_updateQuadTree = BuildQuadTree(&_updateData.GetListQNodes());
	_UpdateListQNodes = _updateData.GetListQNodes();

	_hasData = true;
}

bool LoadGame::HasData()
{
	return this->_hasData;
}

Info* LoadGame::GetInfo()
{
	return this->_Info;
}

CastlePlayer* LoadGame::GetCastlePlayer()
{
	return this->_Mario;
}

QuadTree* LoadGame::GetQuadTree()
{
	return this->_quadTree;
}

QuadTree* LoadGame::GetUpdateQuadTree()
{
	return this->_updateQuadTree;
}

map<int, BaseObject *> & LoadGame::GetListObjects()
{
	return this->_ListObjects;
}

map<int, QNode *> & LoadGame::GetListQNodes()
{
	return this->_ListQNodes;
}

map<int, QNode *> & LoadGame::GetUpdateListQNodes()
{
	return this->_UpdateListQNodes;
}