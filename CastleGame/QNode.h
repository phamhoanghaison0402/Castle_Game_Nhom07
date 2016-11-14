#ifndef _QNODE_H_
#define _QNODE_H_
#include <list>
#include "BaseObject.h"
#include <d3d9.h>
#include <d3dx9.h>

class QNode
{
	QNode *tl, *tr, *bl, *br;
	int _NodeID;
	list<BaseObject*> *_ListObjects;
	RECT _Bound;
public:
	QNode(int id, const RECT &);
	~QNode();
	int GetParentID();
	int GetID();
	void InsertObjects(list<BaseObject*> *ListObjects);
	list<BaseObject*> & GetListObjects();
	void AddChildNode(QNode* node);
	RECT & GetBound();
	QNode* GetChildNode(int i);
	void RemoveObj(BaseObject *);
};
#endif
