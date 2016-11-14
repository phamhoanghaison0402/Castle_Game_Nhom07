#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include "QNode.h"
#include <map>
#include "Factory.h"

class QuadTree
{
	QNode* _RootNode;
	list<BaseObject*> _ListObjInView;
	RECT* _RectWorld;
public:
	QuadTree();
	QuadTree(QNode *root);
	~QuadTree();
	void InsertListObjInView(RECT viewport, QNode* node);
	list<BaseObject*> & GetListObjectsInView();
	QNode* GetRootNode();
	void RemoveObj(BaseObject *, QNode *);
};
#endif