#ifndef _LOADGAME_H_
#define _LOADGAME_H_


#include <list>
#include <map>
#include "Markup.h"
#include <Windows.h>
#include "BaseObject.h"
#include "Build.h"
#include <fstream>

using namespace std;


static map<int, BaseObject *> GListObjects;

class BObject
{
public:
	BaseObject* Deserialize(const char *);
};


class BObjects
{
private:
	list<BaseObject *> _ListObjects;
public:
	void Deserialize(const char *);
	list<BaseObject *> & GetListObjects();
};



struct Info
{
	bool IsSubWorld;
	int nWorld;
	string SubWorld1, SubWorld2;
	D3DXVECTOR2 CreepUpPos1, CreepUpPos2;
	string TheNextWorld;
	D3DXVECTOR2 OriMarioPos;
	int Score, Life, World;
};

class BInfo
{
private:
	Info _Info;
public:
	Info & Deserialize(const char *);
	Info & GetInfo();
};


class BMario
{
public:
	CastlePlayer* Deserialize(const char *);
};


class BQNode
{
	list<BaseObject *>_ListObjects;
public:
	pair<int, QNode *> & Deserialize(const char *);
	list<BaseObject *> & GetListObjects();
};


class BQNodes
{
	map<int, QNode *> _ListQNodes;
public:
	void Deserialize(const char *);
	map<int, QNode *> & GetListNodes();
	list<QNode *> & GetNodes();
};


class BSaveData
{
private:
	int _Width;
	int _Height;
	BQNodes _Nodes;

	Info *_Info;
	CastlePlayer *_Mario;

	map<int, QNode *> _ListQNodes;
	map<int, BaseObject *> _ListObjects;
public:
	void Deserialize(const char *);
	Info* GetInfo();
	CastlePlayer* GetCastlePlayer();
	map<int, QNode *> & GetListQNodes();
	map<int, BaseObject *> & GetListObjects();
};


class LoadGame
{
	BSaveData _data, _updateData;

	Info *_Info;
	CastlePlayer *_Mario;
	bool _hasData;

	QuadTree *_quadTree, *_updateQuadTree;
	map<int, BaseObject *> _ListObjects;
	map<int, QNode *> _ListQNodes, _UpdateListQNodes;
public:
	LoadGame(const char *filename);
	bool HasData();
	Info* GetInfo();
	CastlePlayer* GetCastlePlayer();
	QuadTree* GetQuadTree();
	QuadTree* GetUpdateQuadTree();
	map<int, BaseObject *> & GetListObjects();
	map<int, QNode *> & GetListQNodes();
	map<int, QNode *> & GetUpdateListQNodes();
};

#endif