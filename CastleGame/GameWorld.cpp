#include "GameWorld.h"


GameWorld::GameWorld(DXTexture *backGround)
{
	this->mario = NULL;
	_camera = new Camera();
	this->_backGround = new BaseInfo(backGround, D3DXVECTOR2(0,0));

	this->_isInstance = false;
	this->_IsSubWorld = false;
	this->_isPause = false;
	this->_nWorld = 0;
	this->_isWaitingSwitch = false;
	this->_timeWaiting = 0.0f;
	this->_isFinish = false;
	this->_isGameOver = false;
	this->_isReset = false;
	this->_TheNextWorld = NULL;
}

GameWorld::GameWorld(const char *filemap, DXTexture *backGround, CastlePlayer *&mario, GameInfo *&gameInfo)
{
	this->mario = mario;
	this->_gameInfo = gameInfo;
	this->_backGround = new BaseInfo(backGround, D3DXVECTOR2(0,0));
	_map = new Map(filemap);
	//strcpy(_mapFile, filemap);
	//_map->_Filename = filemap;
	_camera = new Camera();

	this->_isInstance = false;
	this->_IsSubWorld = false;
	this->_isPause = false;
	this->_nWorld = 0;
	this->_isWaitingSwitch = false;
	this->_timeWaiting = 0.0f;
	this->_isFinish = false;
	this->_isGameOver = false;
	this->_isReset = false;
	this->_TheNextWorld = NULL;
}

bool GameWorld::IsInstance()
{
	return this->_isInstance;
}

void GameWorld::Init()
{
	_map->LoadMap();

	_listObjects = *BuildObjectsMap(_map, mario, _CreepUpPos, _flagPosition);
	_quadTree = BuildQuadTree(_map, &_listObjects, EQuadTreeType::DRAW, _listNodes);
	_updateQuadTree = BuildQuadTree(_map, &_listObjects, EQuadTreeType::UPDATE, _listUpdateNodes);

	this->_isInstance = true;
	this->_oriMarioPos = mario->_position;
}



void GameWorld::Cleanup()
{

}

void GameWorld::Pause()
{
	_isPause = true;
}

void GameWorld::Resume()
{
	_isPause = false;
}


void GameWorld::HandleEvents(DXGame *pDXGame)
{
	if (_isPause)
		return;

	if (pDXGame->IsKeyDown(DIK_RIGHT))
	{
		mario->MoveRight();
	}
	else if (pDXGame->IsKeyDown(DIK_LEFT))
	{
		mario->MoveLeft();
	}
	else
	{
		mario->NoneMove();
	}

	if (pDXGame->IsKeyDown(DIK_DOWN))
	{
		mario->Sit();
	}
	else
	{
		mario->NoneSit();
	}

	if (pDXGame->IsKeyDown(DIK_SPACE))
	{	
		mario->Jump();
	}

	if (pDXGame->IsKeyDown(DIK_A))
	{
		mario->Run();
	}
	else
	{
		mario->NoneRun();
	}

	if (pDXGame->IsKeyDown(DIK_Q))
	{
		mario->PhongRoi();
	}
	else
	{
		mario->NonePhongRoi();
	}

	// phóng boomerang
	if (!_last_B && pDXGame->IsKeyDown(DIK_W))
	{		
		mario->ThrowBullet(_listFreeObjects);
		_last_B = true;			
	}
	else if (pDXGame->IsKeyUp(DIK_W))
	{
		_last_B = false;
	}
}


void GameWorld::Update(GameTime* gameTime)
{
	if (_isPause || _isReset || _isGameOver)
		return;
	
	if (_isWaitingSwitch)
	{
		_timeWaiting += gameTime->GetElapsedTimePerFrameMiliSeconds();
		if (_timeWaiting > TIME_OF_WAITING_WORLD)
		{
			_isFinish = true;
			if (_TheNextWorld != NULL)
			{
				_gameInfo->WorldUp();
				/*
				mario->_position = _TheNextWorld->_oriMarioPos;
				_TheNextWorld->SetMario(mario);
				_TheNextWorld->SetGameInfo(_gameInfo);
				*/
			}
		}
		else
		{

		}

		return;
	}
	
	// --------------------------------------- REMOVE ---------------------------------------//
	for (list<BaseObject *>::iterator i = _listDeadObjects.begin(); i != _listDeadObjects.end();)
	{
		RemoveDeadObjects(_listObjects, _quadTree, _updateQuadTree, *i);
		i = _listDeadObjects.erase(i);
	}

	list<BaseObject *>::iterator i;
	// ---------UPDATE-----------------------------------------------------------------------//
	// ----------- MARIO --------------------.//
	mario->Update(gameTime);
	
	if (mario->_SDie == true)
	{
		if (mario->IsDead())
		{
			_gameInfo->LifeDown();
			if (_gameInfo->GetLife() == 0)
			{
				_isGameOver = true;
			}
			else
			{
				_isReset = true;
			}
		}
	}

	// ----------- OTHER ------------//
	_camera->Update(mario->_position);

	//------------- FREE OBJECTs------------------//
	for (i = _listFreeObjects.begin(); i != _listFreeObjects.end();)
	{
		if ( ((DynamicObject *)(*i))->IsDead() )
		{
			i = _listFreeObjects.erase(i); // remove object
			continue;
		}

		(*i)->Update(gameTime);
		i++;
	}

	// --------- ALL OBJECTs in QUADTREE------//
	_quadTree->InsertListObjInView(_camera->_rect, _quadTree->GetRootNode());
	for (i = _quadTree->GetListObjectsInView().begin(); i != _quadTree->GetListObjectsInView().end(); i++)
	{	
		(*i)->Update(gameTime);
	}

	// --------------------END UPDATE---------------------------------------------------------//



	// ----------------- BEGIN COLLISION --------------------//
	//----------------- MARIO -------------------//
	mario->BeginToCheckCollisions();

	// ---------- OBJ in UPDATE QUADTREE---------//
	_updateQuadTree->InsertListObjInView(mario->GetNodeBound(), _updateQuadTree->GetRootNode());
	for (i = _updateQuadTree->GetListObjectsInView().begin(); i != _updateQuadTree->GetListObjectsInView().end(); i++)
	{
		Box *b;
		if (IsMovableObject(*i))
		{
			b = &((DynamicObject *)(*i))->GetBoardBox();
		}
		else
		{
			b = &(*i)->GetObjectBox();
		}

		if (AABBCheck(mario->GetBoardBox(), *b))
		{
			CollisionDirection dir;

			// đối tượng có thể di chuyển
			if (IsMovableLivingObject(*i))
			{
				if ( ((LivingObject *)(*i))->_isDead == true)
				{
					_listDeadObjects.push_back(*i); 
					continue;
				}

				dir = mario->CheckCollisions(*i);
				switch ((*i)->GetType())
				{
					// quái
				case EObjectName::BOSS_1_OBJECT: // OK
					// va chạm vs mario
					if (dir != CollisionDirection::NONE_COL)
					{
						if (mario->_IsImmortality)
						{
							((Enemy *)(*i))->CollisionWithBullet();
							_listDeadObjects.push_back(*i);
							if ((*i)->GetType() == EObjectName::BOSS_1_OBJECT)
							{
								_gameInfo->AddScore(200);
							}
							else if ((*i)->GetType() == EObjectName::BANCHONG_OBJECT)
							{
								_gameInfo->AddScore(400);
							}
							else
							{
								_gameInfo->AddScore(500);
							}
							mario->ResponseAsNoCollision(*i, dir);
							
							continue;
						}
								
					}

					break;

											
				default:
					break;
				}
			}
			else // đối tượng k thể di chuyển
			{
				if ((*i)->GetType() == EObjectName::TOWER_OBJECT)
				{
					if (_last_ArrowUp && !_isWaitingSwitch && AABBCheck(mario->GetObjectBox(), (*i)->GetObjectBox()))
					{
						_isWaitingSwitch = true;
						_timeWaiting = 0.0f;
						_gameInfo->AddScore(5000);
					}
					continue;
				}
				/*else if ((*i)->GetType() == EObjectName::BRICK_OBJECT && ((Brick *)(*i))->_isExplored == true)
				{
					continue;
				}*/

				GameWorld *w;
				dir = mario->CheckCollisions(*i);

				if (dir != CollisionDirection::NONE_COL)
				{
					switch ((*i)->GetType())
					{
					
					//case EObjectName::BRICK_OBJECT: // ok				
					//case EObjectName::CUADONG_OBJECT:
					case EObjectName::GACHNAU_OBJECT:
						// k lam gi ca
						break;

					default:
						break;
					}
				}
			}
		}
	}
	

	
	// ----------- LIVING OBJECT - UPDATING OBJECTs------------------------------//
	list<BaseObject *>::iterator j;
	for (i = _quadTree->GetListObjectsInView().begin(); i != _quadTree->GetListObjectsInView().end(); i++)
	{
		// đối tượng sống
		if (IsMovableLivingObject(*i))
		{
			LivingObject *obj = (LivingObject *)(*i);

			// BEGIN COLLISION
			obj->BeginToCheckCollisions();

			// COLLISION
			// xét va chạm vs các đối tượng xung quanh
			_updateQuadTree->InsertListObjInView(obj->GetNodeBound(), _updateQuadTree->GetRootNode());
			for (j = _updateQuadTree->GetListObjectsInView().begin(); j != _updateQuadTree->GetListObjectsInView().end(); j++)
			{
				if ((*i) == (*j))
					continue;

				Box *b;
				if (IsMovableObject(*j))
				{
					b = &((DynamicObject *)(*j))->GetBoardBox();
				}
				else
				{
					b = &(*j)->GetObjectBox();
				}

				// kiểm tra va chạm
				if (AABBCheck(obj->GetBoardBox(), *b))
				{
					CollisionDirection dir;

					// dối tượng sống
					if (IsMovableLivingObject(*j))
					{
						
					}
					else
					{
						/* if ((*j)->GetType() == EObjectName::BRICK_OBJECT)
						{
							if (((Brick *)(*j))->_isExplored == false)
							{
								dir = obj->CheckCollisions(*j);
								if ( ((Brick *)(*j))->_isMovedUp )
								{
									if (dir == CollisionDirection::TOP_COL) // va chạm trên vs gạch
									{
										if ((*i)->GetType() == EObjectName::ENEMY_OBJECT)
										{
											((Enemy *)(*i))->CollisionWithBullet();
											if ((*i)->GetType() == EObjectName::BANCHONG_OBJECT)
											{
												_gameInfo->AddScore(400);
											}
											/*else if ((*i)->GetType() == EObjectName::TURTLE2_OBJECT )
											{
												_gameInfo->AddScore(500);
											}
											else
											{
												_gameInfo->AddScore(200);
											}
											
										}
									}
								}
							}
						}
						else
						{
							
						}*/
					}
				}
			}

			// RESPONSE COLLISIONs
			obj->ResponseCollisions();
		}
		else
		{
			// do nothing
		}
	}

	// -- free - in quadtree
	for (i = _listFreeObjects.begin(); i != _listFreeObjects.end(); i++)
	{
		DynamicObject *obj = (DynamicObject *)(*i);

		_updateQuadTree->InsertListObjInView(obj->GetNodeBound(), _updateQuadTree->GetRootNode());
		for (j = _updateQuadTree->GetListObjectsInView().begin(); j != _updateQuadTree->GetListObjectsInView().end(); j++)
		{
			/*if ((*j)->GetType() == EObjectName::BRICK_OBJECT && ((Brick *)(*j))->_isExplored == true)
			{
				continue;
			}*/
			if ((*j)->GetType() == EObjectName::TOWER_OBJECT)
			{
				continue;
			}

			if ( obj->IsDead() == false )
			{
				CollisionDirection dir;

				if (IsMovableLivingObject(*j) == true)
				{
					dir = ((LivingObject *)(*j))->CheckCollisions(obj);
					((LivingObject *)(*j))->ResponseCollisions();
				}

				// xử lý obj
				switch (obj->GetType())
				{
				
				default:
					break;
				}
			}
		}

		// -------------
		for (j = _listFreeObjects.begin(); j != _listFreeObjects.end(); j++)
		{
			if ((*i) == (*j) || (*i)->GetType() == EObjectName::BULLET_OBJECT || (*j)->GetType() == EObjectName::BULLET_OBJECT)
				continue;

			if ( Intersect(&((DynamicObject *)(*i))->GetNodeBound(), &((DynamicObject *)(*j))->GetNodeBound()) == false )
				continue;

			if (((LivingObject *)(*i))->_isDead == false)
			{
				((LivingObject *)(*i))->CheckCollisions(*j);
			}
		}
	}


	// ------------ RESPONSE COLLISIONS-----------------------------------------/
	// ------------- MARIO --------------------//
	mario->ResponseCollisions();
}

void GameWorld::Draw(DXGame *pDXGame)
{	
	this->_backGround->Draw(pDXGame);

	if (_isPause || _isReset)
		return;

	// -------------QUADTREE----------------//
	list<BaseObject *>::iterator i;
	for (i = _quadTree->GetListObjectsInView().begin(); i != _quadTree->GetListObjectsInView().end(); i++)
	{
		(*i)->Draw(pDXGame, _camera);
	}

	// --------------FREE OBJECTs-----------//
	for (i = _listFreeObjects.begin(); i != _listFreeObjects.end(); i++)
	{
		(*i)->Draw(pDXGame, _camera);
	}

	//-----------------MARIO----------------//
	if (!_timeWaiting)
	{
		mario->Draw(pDXGame, _camera);
	}

	_gameInfo->Draw(pDXGame, D3DCOLOR_XRGB(255,255,0));
}

bool GameWorld::IsReset()
{
	return _isReset;
}

void GameWorld::SetReset(bool value)
{
	_isReset = value;
}

D3DXVECTOR2 GameWorld::GetResetPosition()
{
	if (!_flagPosition.empty())
	{
		int maxX = _oriMarioPos.x;
		D3DXVECTOR2 *maxPos = &_oriMarioPos;
		for (list<D3DXVECTOR2 *>::iterator i = _flagPosition.begin(); i != _flagPosition.end(); i++)
		{
			if ((*i)->x < mario->_position.x)
			{
				if (maxX < (*i)->x)
				{
					maxX = (*i)->x;
					maxPos = *i;
				}
			}
		}

		return *maxPos;
	}
	else
	{
		return _oriMarioPos;
	}
}

void GameWorld::ResetMarioPosition()
{
	mario->_velocity.y = 0;
	mario->_velocity.x = 0;
	mario->_isDead = false;
	mario->_SDie = false;
	mario->_IsSmaller = false;
	mario->_EatMushroom = false;
	mario->_EatFlower = false;
	mario->_position = this->GetResetPosition();
}

bool GameWorld::IsFinish()
{
	return _isFinish;
}

bool GameWorld::IsGameOver()
{
	return _isGameOver;
}

void GameWorld::AddSubWorld(GameWorld *world)
{
	world->_IsSubWorld = true;
	this->_ListSubWorld[_nWorld++] = world;
}



GameWorld* GameWorld::GetSubWorld(int n)
{
	if (_nWorld == 0)
		return NULL;

	if (n < 0)
	{
		n = 0;
	}
	else if (n >= _nWorld)
	{
		n = _nWorld - 1;
	}

	return this->_ListSubWorld[n];
}

void GameWorld::RemoveAllSubWorld()
{
	_nWorld = 0;

	if (this->_ListSubWorld[0] != NULL)
	{
		delete this->_ListSubWorld[0];
		this->_ListSubWorld[0] = NULL;
	}

	if (this->_ListSubWorld[1] != NULL)
	{
		delete this->_ListSubWorld[1];
		this->_ListSubWorld[1] = NULL;
	}
}

void GameWorld::AddTheNextWorld(GameWorld *world)
{
	_TheNextWorld = world;
}

void GameWorld::SetMario(CastlePlayer *&mario)
{
	this->mario = mario;
}

CastlePlayer* GameWorld::GetMario()
{
	return this->mario;
}

void GameWorld::SetGameInfo(GameInfo *&gameInfo)
{
	this->_gameInfo = gameInfo;
}

GameInfo* GameWorld::GetGameInfo()
{
	return this->_gameInfo;
}

bool GameWorld::HasTheNextWorld()
{
	if (_TheNextWorld != NULL)
		return true;

	return false;
}

GameWorld* GameWorld::GetTheNextWorld()
{
	return _TheNextWorld;
}

