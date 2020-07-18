#pragma once

#include "FunctionFwd.hpp"
#include "Psx.hpp"

START_NS_AO

EXPORT signed __int16 CC Pal_Allocate_4476F0(PSX_RECT* pRect, unsigned int paletteColorCount);

EXPORT void CC Pal_Free_447870(PSX_Point xy, __int16 palDepth);

EXPORT void CC Pal_Copy_4479D0(PSX_Point point, __int16 w, WORD* pPalData, PSX_RECT* rect);

EXPORT void CC Pal_Set_447990(PSX_Point xy, __int16 w, const BYTE* palData, PSX_RECT* rect);

EXPORT unsigned int CC Pal_Make_Colour_447950(BYTE r, BYTE g, BYTE b, __int16 bOpaque);

END_NS_AO