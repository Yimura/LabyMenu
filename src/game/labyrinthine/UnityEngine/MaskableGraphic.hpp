#pragma once
#include "Graphic.hpp"

namespace YimMenu
{
    class UnityEngine_UI_MaskableGraphic_Fields : public UnityEngine_UI_Graphic_Fields
    {
    public:
        bool m_ShouldRecalculateStencil;
        struct UnityEngine_Material_o *m_MaskMaterial;
        struct UnityEngine_UI_RectMask2D_o *m_ParentMask;
        bool m_Maskable;
        bool m_IsMaskingGraphic;
        bool m_IncludeForMasking;
        struct UnityEngine_UI_MaskableGraphic_CullStateChangedEvent_o *m_OnCullStateChanged;
        bool m_ShouldRecalculate;
        int32_t m_StencilValue;
        struct UnityEngine_Vector3_array *m_Corners;
    };
}
