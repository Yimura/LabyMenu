#pragma once
#include <cstdint>
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace YimMenu
{
    struct RaycastHit
    {
        Vector3 m_Point;
        Vector3 m_Normal;
        uint32_t m_FaceID;
        float m_Distance;
        Vector2 m_UV;
        int32_t m_Collider;
    };
}
