#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "BaseObject.h"


static bool IsCollisionableObject(BaseObject *obj)
{
	switch (obj->GetType())
	{
	case EObjectName::BACKGROUND_BLUE_OBJECT:

	case EObjectName::NENGACH_TRAI_OBJECT:
	case EObjectName::NGONDUOC_OBJECT:
	case EObjectName::NGONNEN_OBJECT:
	case EObjectName::TRU_OBJECT:
		return false;
		break;

	default:
		return true;
		break;
	}
}

static bool IsMovableObject(BaseObject *obj)
{
	switch (obj->GetType())
	{
	case EObjectName::BOSS_1_OBJECT:
	case EObjectName::BANCHONG_OBJECT:

		return true;
		break;
	default:
		return false;
		break;
	}
}

static bool IsMovableLivingObject(BaseObject *obj)
{
	switch (obj->GetType())
	{
	case EObjectName::BOSS_1_OBJECT:
	case EObjectName::BANCHONG_OBJECT:
		return true;
		break;
	default:
		return false;
		break;
	}
}

#endif
