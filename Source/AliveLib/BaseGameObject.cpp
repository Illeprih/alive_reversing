#include "stdafx.h"
#include "BaseGameObject.hpp"
#include "Function.hpp"

ALIVE_VAR(1, 0xBB47C4, DynamicArrayT<BaseGameObject>*, gBaseGameObject_list_BB47C4, nullptr);

void BaseGameObject::VUpdate()
{
    // Empty 0x4DC080
}

void BaseGameObject::VRender(int** /*pOrderingTable*/)
{
    // Empty 0x4DBF80
}

void BaseGameObject::vsub_4DC0A0()
{
    NOT_IMPLEMENTED();
}

void BaseGameObject::vnullsub_4DC0F0()
{
    // Empty 0x4DC0F0
}

int BaseGameObject::GetSaveState_4DC110(BYTE* /*pSaveBuffer*/)
{
    return 0;
}

ALIVE_VAR(1, 0x5C1BF4, int, sAccumulatedObjectCount_5C1BF4, 0);

ALIVE_VAR(1, 0x5C1B70, Class_5C1B70, dword_5C1B70, {});


void BaseGameObject::ctor_4DBFA0(__int16 bAddToObjectList, signed __int16 resourceArraySize)
{
    field_10_resources_array.ctor_40C9E0(resourceArraySize);
    field_1C_update_delay = 0;
    field_4_typeId = 0;
    field_6_flags = field_6_flags & 0xF80A | 2;

    if (bAddToObjectList)
    {
        if (!gBaseGameObject_list_BB47C4->Push_Back(this))
        {
            field_6_flags |= 1u;
        }
    }

    field_C_objectId = sAccumulatedObjectCount_5C1BF4;
    field_8_flags_ex = sAccumulatedObjectCount_5C1BF4;
    const int nextId = sAccumulatedObjectCount_5C1BF4++;
    dword_5C1B70.sub_449C10(nextId, this);
}

EXPORT void Class_5C1B70::sub_449C10(int objCount, void* pGameObj)
{
    NOT_IMPLEMENTED();
}
