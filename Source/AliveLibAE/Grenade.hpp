#pragma once

#include "Throwable.hpp"

enum class GrenadeStates : __int16
{
    eFallingToBeCollected_0 = 0,
    eWaitToBeCollected_1 = 1,
    eDoesNothing_2 = 2,
    eCountingDown_3 = 3,
    eFalling_4 = 4,
    eHitGround_5 = 5,
    eWaitForExplodeEnd_6 = 6,
    eExploded_7 = 7,
    eDoesNothing_8 = 8,
    eFallingBlowUpOnGround_9 = 9,
};

struct Grenade_SaveState
{
    Types field_0_type;
    __int16 field_2_pad;
    int field_4_obj_id;
    FP field_8_xpos;
    FP field_C_ypos;
    FP field_10_velx;
    FP field_14_vely;
    FP field_18_sprite_scale;
    __int16 field_1C_path_number;
    LevelIds field_1E_lvl_number;

    enum Flags_20
    {
        eBit1_bRender = 0x1,
        eBit2_bDrawable = 0x2,
        eBit3_bLoop = 0x4,
        eBit4_bInteractive = 0x8,
        eBit5_unused = 0x10,
        eBit6_bExplodeNow = 0x20,
        eBit7_bBlowUpOnCollision = 0x40,
    };
    BitField16<Flags_20> field_20_flags;
    __int16 field_22_padding;
    int field_24_base_id;
    __int16 field_28_line_type;
    __int16 field_2A_savedcount;
    GrenadeStates field_2C_state;
    __int16 field_2E;
    __int16 field_30_explode_timer;
    __int16 field_32_padding;
    FP field_34_xpos;
    FP field_38_ypos;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Grenade_SaveState, 0x3C);

class Grenade : public BaseThrowable
{
public:
    EXPORT Grenade* ctor_447F70(FP xpos, FP ypos, __int16 numGrenades, __int16 a5, __int16 a6, BaseGameObject* pOwner);

    virtual BaseGameObject* VDestructor(signed int flags) override;

    virtual void VScreenChanged() override;

    virtual int VGetSaveState(BYTE* pSaveBuffer) override;

    virtual void VUpdate() override;

    virtual void VOnTrapDoorOpen() override;

    virtual void VThrow_49E460(FP velX, FP velY) override;

    virtual BOOL VCanThrow_49E350() override;

    virtual BOOL VIsFalling_49E330() override;

    virtual void VTimeToExplodeRandom_411490() override;


    // Next 2 virtuals are base

    EXPORT static int CC CreateFromSaveState_449410(const BYTE* pBuffer);

private:
    EXPORT int GetSaveState_4496B0(Grenade_SaveState* pState);


    EXPORT void vScreenChanged_449140();


    EXPORT void Init_448110(FP xpos, FP ypos);

    EXPORT void vOnTrapDoorOpen_449390();


    EXPORT void vThrow_4482E0(FP velX, FP velY);

    EXPORT BOOL vCanThrow_49A5F0();

    EXPORT BOOL vIsFalling_49A610();

    EXPORT void vTimeToExplodeRandom_4480A0();

    EXPORT void BlowUp_4483C0(__int16 bSmallExplosion);

    EXPORT void dtor_448220();

    EXPORT Grenade* vdtor_4480E0(signed int flags);

    EXPORT signed __int16 TimeToBlowUp_448350();

    EXPORT void vUpdate_4489C0();

    EXPORT __int16 InTheAir_4484F0(__int16 blowUpOnFloorTouch);

    EXPORT void AddToPlatform_449210();

    EXPORT __int16 OnCollision_BounceOff_448F90(BaseGameObject* pHit);

    EXPORT __int16 OnCollision_InstantExplode_4490D0(BaseGameObject* pHit);


    /*
    Grenade__vOnTrapDoorOpen_449390
    Grenade__vThrow_4482E0
    Grenade__vCanThrow_49A5F0 // Always 0 ??
    Grenade__vIsFalling_49A610 // Always 0 ??
    Grenade__vTimeToExplodeRandom_4480A0
    Rock__vGetCount_448080
    BaseThrowable__vToDead_4114B0
    */

private:
    int field_11C_explosion_id;
    GrenadeStates field_120_state;
    __int16 field_122_explode_timer;
    __int16 field_124;
    __int16 field_126_input;
    FP field_128_xpos;
    FP field_12C_ypos;
    __int16 field_130_unused;
    __int16 field_132_bBlowUpOnCollision;
    __int16 field_134_bExplodeNow;
    __int16 field_136_padding;
    BaseGameObject* field_138_pOwner;
};
ALIVE_ASSERT_SIZEOF(Grenade, 0x13C);
