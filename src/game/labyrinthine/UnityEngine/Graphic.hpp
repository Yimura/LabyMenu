#pragma once
#include "Color.hpp"
#include "UIBehaviour.hpp"
#include "Vector4.hpp"

namespace YimMenu
{
    class UnityEngine_UI_Graphic_Fields : public UnityEngine_EventSystems_UIBehaviour_Fields
    {
    private:
        struct UnityEngine_Material_o *m_Material;
        Color m_Color;
        bool m_SkipLayoutUpdate;
        bool m_SkipMaterialUpdate;
        bool m_RaycastTarget;
        Vector4 m_RaycastPadding;
        struct UnityEngine_RectTransform_o *m_RectTransform;
        struct UnityEngine_CanvasRenderer_o *m_CanvasRenderer;
        struct UnityEngine_Canvas_o *m_Canvas;
        bool m_VertsDirty;
        bool m_MaterialDirty;
        struct UnityEngine_Events_UnityAction_o *m_OnDirtyLayoutCallback;
        struct UnityEngine_Events_UnityAction_o *m_OnDirtyVertsCallback;
        struct UnityEngine_Events_UnityAction_o *m_OnDirtyMaterialCallback;
        struct UnityEngine_Mesh_o *m_CachedMesh;
        struct UnityEngine_Vector2_array *m_CachedUvs;
        struct UnityEngine_UI_CoroutineTween_TweenRunner_ColorTween__o *m_ColorTweenRunner;
        bool _useLegacyMeshGeneration_k__BackingField;
    };
}
