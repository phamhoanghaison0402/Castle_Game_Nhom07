#include "Collision.h"


Collision::Collision()
{
	_moveX = 0.0f;
	_moveY = 0.0f;
	_flagCollisionX = 0;
	_flagCollisionY = 0;
}

void Collision::BeginToCheckCollisions()
{
	_moveX = 0.0f;
	_moveY = 0.0f;
	_flagCollisionX = 0;
	_flagCollisionY = 0;
}

void Collision::TopCol(BaseObject *obj)
{
	_flagCollisionY = 1;
}

void Collision::BottomCol(BaseObject *obj)
{
	_flagCollisionY = -1;
}

void Collision::LeftCol(BaseObject *obj)
{
	_flagCollisionX = -1;
}

void Collision::RightCol(BaseObject *obj)
{
	_flagCollisionX = 1;
}

CollisionDirection Collision::CheckCollisions(DynamicObject *curObj, BaseObject *obj)
{
	float normalx, normaly;
	float collisionTime;
	float moveX, moveY;
	D3DXVECTOR2 tmpVelocity;
	DynamicObject *o;

	if (AABB(curObj->GetObjectBox(), obj->GetObjectBox(), moveX, moveY) == false)
	{
		if (IsMovableObject(obj))
		{
			o = (DynamicObject *)obj;
			tmpVelocity = D3DXVECTOR2(curObj->_velocity.x - o->_velocity.x, curObj->_velocity.y - o->_velocity.y);
		}
		else
		{
			tmpVelocity = curObj->_velocity;
		}

		// bắt đầu kiểm tra va chạm
		if (AABB(curObj->GetBoardBox(tmpVelocity), obj->GetObjectBox(), moveX, moveY) == true) // dong
		{
			collisionTime = SweptAABB(
				curObj->GetNonStaticObjectBox(),
				obj->GetObjectBox(),
				normalx, normaly
				);

			if (collisionTime > 0 && collisionTime < 1)
			{
				if (abs(_moveX) < abs(curObj->_velocity.x * curObj->_deltaTime * collisionTime + normalx))
				{
					_moveX = curObj->_velocity.x * curObj->_deltaTime * collisionTime + normalx;
				}
				if (abs(_moveY) < abs(curObj->_velocity.y * curObj->_deltaTime * collisionTime + normaly))
				{
					_moveY = curObj->_velocity.y * curObj->_deltaTime * collisionTime + normaly;
				}

				if (normaly != 0)
				{
					if (moveY != 0)
					{
 						if (normaly == 1.0f)
						{
							TopCol(obj);
							return CollisionDirection::TOP_COL;
						}
						else if (normaly == -1.0f)
						{
							BottomCol(obj);
							return CollisionDirection::BOTTOM_COL;
						}
					}
				}
				else
				{
					if (moveX != 0)
					{
						if (normalx == -1.0f)
						{
							LeftCol(obj);
							return CollisionDirection::LEFT_COL;
						}
						else if (normalx == 1.0f)
						{
							RightCol(obj);
							return CollisionDirection::RIGHT_COL;
						}
					}
				}
			}
		}
		else // tinh
		{
			if (AABBCheck1(curObj->GetBoardBox(D3DXVECTOR2(0, -300)), obj->GetObjectBox()) == true)
			{
				TopCol(obj);
				return CollisionDirection::TOP_COL;
			}
		}
	}
	else
	{
   		if (moveX != 0)
		{
			if (abs(_moveX) < abs(moveX))
			{
				_moveX = moveX;
			}

	 		if (moveX < 0)
			{
				LeftCol(obj);
				return CollisionDirection::LEFT_COL;
			}
			else
			{
				RightCol(obj);
				return CollisionDirection::RIGHT_COL;
			}
		}
		else if (moveY != 0)
		{
			if (abs(_moveY) < abs(moveY))
			{
				_moveY = moveY;
			}

			if (moveY > 0)
			{
				TopCol(obj);
				return CollisionDirection::TOP_COL;
			}
			else
			{
				BottomCol(obj);
				return CollisionDirection::BOTTOM_COL;
			}
		}
		else
		{
			if ((curObj->_rect.bottom == obj->_rect.top && curObj->_rect.right == obj->_rect.left)
				|| (curObj->_rect.bottom == obj->_rect.top && obj->_rect.right == curObj->_rect.left))
			{
				return CollisionDirection::NONE_COL;
			}
			
			if (curObj->_rect.bottom == obj->_rect.top)
			{
				curObj->_position.y += 1;
				TopCol(obj);
				return CollisionDirection::TOP_COL;
			}
			else if (curObj->_rect.top == obj->_rect.bottom)
			{
				curObj->_position.y -= 1;
				BottomCol(obj);
				return CollisionDirection::BOTTOM_COL;
			}
			else if (curObj->_rect.right == obj->_rect.left)
			{
				LeftCol(obj);
				return CollisionDirection::LEFT_COL;
			}
			else if (curObj->_rect.left == obj->_rect.right)
			{
				RightCol(obj);
				return CollisionDirection::RIGHT_COL;
			}
		}
	}

	return CollisionDirection::NONE_COL;
}

D3DXVECTOR2 Collision::TransferPosition(D3DXVECTOR2 &pos)
{
	pos.x += _moveX;
	pos.y += _moveY;
	return pos;
}