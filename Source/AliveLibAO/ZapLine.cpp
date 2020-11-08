#include "stdafx_ao.h"
#include "Function.hpp"
#include "ZapLine.hpp"
#include "stdlib.hpp"
#include "ResourceManager.hpp"
#include "Map.hpp"
#include "PsxDisplay.hpp"
#include "ScreenManager.hpp"
#include "Game.hpp"
#include "Math.hpp"

void ZapLine_ForceLink() {}

START_NS_AO

BaseGameObject* ZapLine::VDestructor(signed int flags)
{
    return Vdtor_479B20(flags);
}

BaseGameObject* ZapLine::dtor_478E90()
{
    SetVTable(this, 0x4BCDE8);
    ResourceManager::FreeResource_455550(field_E8_ppRes);
    ao_delete_free_450770(field_128_sprite_positions);
    ao_delete_free_450770(field_12C_zap_points);
    ao_delete_free_450770(field_130_sprite_segment_positions);
    return dtor_417D10();
}

ZapLine* ZapLine::ctor_4789A0(FP x1, FP y1, FP x2, FP y2, __int16 aliveTime, ZapLineType type, __int16 layer)
{
    ctor_417C10();
    SetVTable(this, 0x4BCDE8);

    field_4_typeId = Types::eZapLine_94;
    field_11A_type = type;

    int frameTable = 0;
    if (field_11A_type == ZapLineType::eThin_1)
    {
        field_120_number_of_pieces_per_segment = 20;
        field_11E_number_of_segments = 12;
        frameTable = 228;
        field_11C_tPageAbr = 3;
    }
    else if (field_11A_type == ZapLineType::eThick_0)
    {
        field_120_number_of_pieces_per_segment = 10;
        field_11E_number_of_segments = 28;
        frameTable = 240;
        field_11C_tPageAbr = 1;
    }

    BYTE** ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, 355, 1, 0);
    Animation_Init_417FD0(frameTable, 9, 9, ppRes, 1);

    field_10_anim.field_4_flags.Clear(AnimFlags::eBit15_bSemiTrans);
    field_10_anim.field_C_layer = layer;
    field_122_number_of_sprites = field_11E_number_of_segments * field_120_number_of_pieces_per_segment;

    field_E8_ppRes = ResourceManager::Allocate_New_Locked_Resource_454F80(ResourceManager::Resource_Spline, 0, sizeof(ZapLineSprites) * field_122_number_of_sprites
    );
    field_124_pSprts = reinterpret_cast<ZapLineSprites*>(*field_E8_ppRes);

    field_128_sprite_positions = reinterpret_cast<PSX_Point*>(alloc_450740(sizeof(PSX_Point) * field_122_number_of_sprites));
    field_12C_zap_points = reinterpret_cast<ZapPoint*>(alloc_450740(sizeof(ZapPoint) * field_120_number_of_pieces_per_segment));
    field_130_sprite_segment_positions = reinterpret_cast<FP_Point*>(alloc_450740(sizeof(FP_Point) * field_11E_number_of_segments));

    field_118_max_alive_time = aliveTime;

    field_A8_xpos = x1;
    field_AC_ypos = y1;

    field_E4_state = ZapLineState::eInit_0;
    field_116_alive_timer = 0;

    if (field_10_anim.field_4_flags.Get(AnimFlags::eBit13_Is8Bit))
    {
        field_114_tPageMode = 1;
    }
    else if (field_10_anim.field_4_flags.Get(AnimFlags::eBit14_Is16Bit))
    {
        field_114_tPageMode = 2;
    }
    else
    {
        field_114_tPageMode = 0;
    }

    BYTE u0 = field_10_anim.field_84_vram_rect.x & 0x3F;
    if (field_114_tPageMode == 1)
    {
        u0 = 2 * u0;
    }
    else if (!field_114_tPageMode)
    {
        u0 = 4 * u0;
    }

    auto pFrameHeader = reinterpret_cast<FrameHeader*>(&(*field_10_anim.field_20_ppBlock)[field_10_anim.Get_FrameHeader_403A00(-1)->field_0_frame_header_offset]);

    const BYTE frameW = pFrameHeader->field_4_width;
    const BYTE frameH = pFrameHeader->field_5_height;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < field_11E_number_of_segments; j++)
        {
            for (int k = 0; k < field_120_number_of_pieces_per_segment; k++)
            {
                  Prim_Sprt* pSprt = &field_124_pSprts[(j * field_120_number_of_pieces_per_segment) + k].field_0_sprts[i];
                  Sprt_Init(pSprt);

                  Poly_Set_SemiTrans_498A40(&pSprt->mBase.header, 1);
                  Poly_Set_Blending_498A00(&pSprt->mBase.header, 1);
                  SetClut(pSprt, static_cast<short>(PSX_getClut_496840(
                      field_10_anim.field_8C_pal_vram_xy.field_0_x,
                      field_10_anim.field_8C_pal_vram_xy.field_2_y)));

                  SetUV0(pSprt, u0, field_10_anim.field_84_vram_rect.y & 0xFF);
                  pSprt->field_14_w = frameW - 1;
                  pSprt->field_16_h = frameH - 1;
            }
        }
    }

    CalculateSourceAndDestinationPositions_478CF0(x1, y1, x2, y2);

    return this;
}

ZapLine* ZapLine::Vdtor_479B20(signed int flags)
{
    dtor_478E90();
    if (flags & 1)
    {
        ao_delete_free_447540(this);
    }
    return this;
}

void ZapLine::CalculateSourceAndDestinationPositions_478CF0(FP xPosSource, FP yPosSource, FP xPosDest, FP yPosDest)
{
    field_10C_x_position_source = FP_GetExponent(xPosSource - (pScreenManager_4FF7C8->field_10_pCamPos->field_0_x - FP_FromInteger(pScreenManager_4FF7C8->field_14_xpos)));
    field_10E_y_position_source = FP_GetExponent(yPosSource - (pScreenManager_4FF7C8->field_10_pCamPos->field_4_y - FP_FromInteger(pScreenManager_4FF7C8->field_16_ypos)));
    field_110_x_position_destination = FP_GetExponent(xPosDest - (pScreenManager_4FF7C8->field_10_pCamPos->field_0_x - FP_FromInteger(pScreenManager_4FF7C8->field_14_xpos)));
    field_112_y_position_destination = FP_GetExponent(yPosDest - (pScreenManager_4FF7C8->field_10_pCamPos->field_4_y - FP_FromInteger(pScreenManager_4FF7C8->field_16_ypos)));

    field_10C_x_position_source = PsxToPCX(field_10C_x_position_source, 11);
    field_110_x_position_destination = PsxToPCX(field_110_x_position_destination, 11);

    __int16 xOff = 0;
    __int16 yOff = 0;
    field_10_anim.Get_Frame_Offset_403EE0(&xOff, &yOff);

    field_10C_x_position_source = FP_GetExponent(FP_FromInteger(xOff) + FP_FromInteger(field_10C_x_position_source));
    field_10E_y_position_source = FP_GetExponent(FP_FromInteger(yOff) + FP_FromInteger(field_10E_y_position_source));
    field_110_x_position_destination = FP_GetExponent(FP_FromInteger(xOff) + FP_FromInteger(field_110_x_position_destination));
    field_112_y_position_destination = FP_GetExponent(FP_FromInteger(yOff) + FP_FromInteger(field_112_y_position_destination));
}

void ZapLine::VScreenChanged()
{
    VScreenChanged_479B00();
}

void ZapLine::VScreenChanged_479B00()
{
    if (gMap_507BA8.field_28_cd_or_overlay_num != gMap_507BA8.GetOverlayId_4440B0())
    {
        field_6_flags.Set(BaseGameObject::eDead_Bit3);
    }
}

void ZapLine::VRender(int** ppOt)
{
    VRender_479840(ppOt);
}

void ZapLine::VRender_479840(int** /*ppOt*/)
{
    NOT_IMPLEMENTED();
}

void ZapLine::VUpdate()
{
    VUpdate_4796B0();
}

void ZapLine::VUpdate_4796B0()
{
    field_116_alive_timer++;

    switch (field_E4_state)
    {
    case ZapLineState::eInit_0:
        CalculateZapPoints_479380();

        if (field_11A_type == ZapLineType::eThin_1)
        {
            CalculateThinSpriteSegmentPositions_4791F0();
        }
        else if (field_11A_type == ZapLineType::eThick_0)
        {
            CalculateThickSpriteSegmentPositions_478F20();
        }
        field_E4_state = ZapLineState::eInitSpritePositions_1;
        break;

    case ZapLineState::eInitSpritePositions_1:
        CalculateSpritePositionsOuter();
        field_E4_state = ZapLineState::eInitSpriteVertices_2;
        break;

    case ZapLineState::eInitSpriteVertices_2:
    case ZapLineState::eUpdateSpriteVertices_4:
        UpdateSpriteVertexPositions_4795B0();

        if (field_116_alive_timer >= field_118_max_alive_time && field_11A_type != ZapLineType::eThin_1)
        {
            field_6_flags.Set(BaseGameObject::eDead_Bit3);
            return;
        }

        if (field_11A_type == ZapLineType::eThin_1)
        {
            CalculateThinSpriteSegmentPositions_4791F0();
        }
        else if (field_11A_type == ZapLineType::eThick_0)
        {
            CalculateThickSpriteSegmentPositions_478F20();
        }
        field_E4_state = ZapLineState::eUpdateSpritePositions_3;
        break;

    case ZapLineState::eUpdateSpritePositions_3:
        CalculateSpritePositionsOuter();
        field_E4_state = ZapLineState::eUpdateSpriteVertices_4;
        break;
    }
}

void ZapLine::CalculateSpritePositionsOuter()
{
    for (short i = 0; i < field_11E_number_of_segments; i++)
    {
        if (i == 0)
        {
            // First item.
            CalculateSpritePositionsInner_479400(0, 0, 1, 0);
        }
        else
        {
            const short lastIdx = field_11E_number_of_segments - 1;
            if (i == lastIdx)
            {
                // Last item.
                CalculateSpritePositionsInner_479400(field_11E_number_of_segments - 2, lastIdx, lastIdx, field_11E_number_of_segments - 1);
            }
            else
            {
                // Other items.
                CalculateSpritePositionsInner_479400(i - 1, i, i + 1, i);
            }
        }
    }
}

void ZapLine::CalculateZapPoints_479380()
{
    FP acc = FP_FromInteger(0);
    const FP delta = FP_FromInteger(1) / FP_FromInteger(field_120_number_of_pieces_per_segment);
    for (int i = 0; i < field_120_number_of_pieces_per_segment; i++)
    {
        const FP accSqrd = (acc * acc);
        field_12C_zap_points[i].field_0 = accSqrd - FP_FromRaw(2 * acc.fpValue) + FP_FromInteger(1);
        field_12C_zap_points[i].field_4 = -FP_FromRaw(2 * accSqrd.fpValue) + FP_FromRaw(2 * acc.fpValue) + FP_FromInteger(1);
        field_12C_zap_points[i].field_8 = accSqrd;
        acc += delta;
    }
}

void ZapLine::CalculateThinSpriteSegmentPositions_4791F0()
{
    NOT_IMPLEMENTED();
}

void ZapLine::CalculateThickSpriteSegmentPositions_478F20()
{
    int v1 = 0;
    if (field_116_alive_timer >= 8)
    {
        const int v4 = field_118_max_alive_time - field_116_alive_timer;
        if (v4 >= 8)
        {
            v1 = 4;
        }
        else
        {
            v1 = (v4 / 4) + 3;
        }
    }
    else
    {
        v1 = (field_116_alive_timer / 4) + 3;
    }

    int v5 = 1 << v1;
    int v6 = 1 << (v1 - 1);

    field_130_sprite_segment_positions[0].field_0_x = FP_FromInteger(field_10C_x_position_source);
    field_130_sprite_segment_positions[0].field_4_y = FP_FromInteger(field_10E_y_position_source);

    field_130_sprite_segment_positions[field_11E_number_of_segments - 1].field_0_x = FP_FromInteger(field_110_x_position_destination);
    field_130_sprite_segment_positions[field_11E_number_of_segments - 1].field_4_y = FP_FromInteger(field_112_y_position_destination);
    
    int angExtra = 0;
    if ((gnFrameCount_507670 / 8) & 1)
    {
        angExtra = 0;
    }
    else
    {
        angExtra = 128;
    }

    const FP xDiff = FP_FromInteger(field_110_x_position_destination - field_10C_x_position_source) / FP_FromInteger(field_11E_number_of_segments);
    const FP xDiffDiv = (-xDiff * FP_FromDouble(1.5));

    const FP yDiff = FP_FromInteger(field_112_y_position_destination - field_10E_y_position_source) / FP_FromInteger(field_11E_number_of_segments);
    const FP yDiffDiv = (yDiff * FP_FromDouble(1.5));

    for (int i = 1; i < field_11E_number_of_segments - 1; i++)
    {
        const BYTE ang = static_cast<BYTE>(angExtra + 18 * i);

        field_130_sprite_segment_positions[i].field_0_x = 
            FP_FromInteger(Math_NextRandom() % v5) + (Math_Cosine_4510A0(ang) * xDiffDiv) + FP_FromInteger(field_10C_x_position_source) + (FP_FromInteger(i) * xDiff) - FP_FromInteger(v6);

        field_130_sprite_segment_positions[i].field_4_y = 
            FP_FromInteger(Math_NextRandom() % v5) + (Math_Cosine_4510A0(ang) * yDiffDiv) + FP_FromInteger(field_10E_y_position_source) + (FP_FromInteger(i) * yDiff) - FP_FromInteger(v6);

    }

    field_134_rects[0].x = 0;
    field_134_rects[0].y = 0;
    field_134_rects[0].w = gPsxDisplay_504C78.field_0_width;
    field_134_rects[0].h = gPsxDisplay_504C78.field_2_height;

    field_134_rects[1].x = 0;
    field_134_rects[1].y = 0;
    field_134_rects[1].w = gPsxDisplay_504C78.field_0_width;;
    field_134_rects[1].h = gPsxDisplay_504C78.field_2_height;
}

void ZapLine::UpdateSpriteVertexPositions_4795B0()
{
    for (int i = 0; i < field_11E_number_of_segments; i++)
    {
        for (int j = 0; j < field_120_number_of_pieces_per_segment; j++)
        {
            const auto pPoint = &field_128_sprite_positions[j + (i * field_120_number_of_pieces_per_segment)];
            Prim_Sprt* pSprt = &field_124_pSprts->field_0_sprts[j + (i * field_120_number_of_pieces_per_segment)];
            SetXY0(&pSprt[0], pPoint->field_0_x, pPoint->field_2_y);
            SetXY0(&pSprt[1], pPoint->field_0_x, pPoint->field_2_y);
        }
    }
}

void ZapLine::CalculateSpritePositionsInner_479400(int idx1, int idx2, int idx3, __int16 idx4)
{
    const FP x1 = field_130_sprite_segment_positions[idx1].field_0_x;
    const FP y1 = field_130_sprite_segment_positions[idx1].field_4_y;

    const FP x2 = field_130_sprite_segment_positions[idx2].field_0_x;
    const FP y2 = field_130_sprite_segment_positions[idx2].field_4_y;

    const FP x3 = field_130_sprite_segment_positions[idx3].field_0_x;
    const FP y3 = field_130_sprite_segment_positions[idx3].field_4_y;

    for (int i = 0; i < field_120_number_of_pieces_per_segment; i++)
    {
        auto pItem = &field_128_sprite_positions[i + (idx4 * field_120_number_of_pieces_per_segment)];

        pItem->field_0_x = FP_GetExponent(
            FP_FromRaw((
                (field_12C_zap_points[i].field_8 * x3) +
                (field_12C_zap_points[i].field_4 * x2) +
                (field_12C_zap_points[i].field_0 * x1)).fpValue >> 1));

        pItem->field_2_y = FP_GetExponent(
            FP_FromRaw((
                (field_12C_zap_points[i].field_8 * y3) +
                (field_12C_zap_points[i].field_4 * y2) +
                (field_12C_zap_points[i].field_0 * y1)).fpValue >> 1));
    }
}

END_NS_AO
