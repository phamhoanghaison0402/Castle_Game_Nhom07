#include "QuadTree.h"

QuadTree::QuadTree()
{
	this->_RootNode = NULL;
	this->_RectWorld = NULL;
}

QuadTree::QuadTree(QNode *root)
{
	this->_RootNode = root;
}

void QuadTree::InsertListObjInView(RECT viewport, QNode* node)
{
	if (this->_RootNode == node)
	{
		this->_ListObjInView.clear();
	}

	if (node->GetChildNode(1) ==  NULL)
	{
		if (Intersect(&node->GetBound(), &viewport))
		{
			list<BaseObject *>::iterator i, j;
			for (i = node->GetListObjects().begin(); i != node->GetListObjects().end(); i++)
			{
				// kiểm tra xem obj đã tồn tại trong list chưa
				for (j = this->_ListObjInView.begin(); j != this->_ListObjInView.end(); j++)
				{
					if ((*i) == (*j))
					{
						break;
					}
				}

				// nếu chưa tồn tại, duyệt hết mảng
				if (j == this->_ListObjInView.end())
				{
					if (IsCollisionableObject(*i) == false || (*i)->GetType() == EObjectName::TOWER_OBJECT)
					{
						this->_ListObjInView.push_front(*i);
					}
					else
					{
						this->_ListObjInView.push_back(*i);
					}
				}
			}
		}
	}
	else
	{
		if (Intersect(&node->GetChildNode(1)->GetBound(), &viewport))
		{
			InsertListObjInView(viewport, node->GetChildNode(1));
		}
		if (Intersect(&node->GetChildNode(2)->GetBound(), &viewport))
		{
			InsertListObjInView(viewport, node->GetChildNode(2));
		}
		if (Intersect(&node->GetChildNode(3)->GetBound(), &viewport))
		{
			InsertListObjInView(viewport, node->GetChildNode(3));
		}
		if (Intersect(&node->GetChildNode(4)->GetBound(), &viewport))
		{
			InsertListObjInView(viewport, node->GetChildNode(4));
		}
	}
}

list<BaseObject*> & QuadTree::GetListObjectsInView()
{
	return this->_ListObjInView;
}

QNode* QuadTree::GetRootNode()
{
	return _RootNode;
}

void QuadTree::RemoveObj(BaseObject *obj, QNode *node)
{
	if (node->GetChildNode(1) == NULL)
	{
		node->RemoveObj(obj);
	}
	else
	{
		this->RemoveObj(obj, node->GetChildNode(1));
		this->RemoveObj(obj, node->GetChildNode(2));
		this->RemoveObj(obj, node->GetChildNode(3));
		this->RemoveObj(obj, node->GetChildNode(4));
	}
}