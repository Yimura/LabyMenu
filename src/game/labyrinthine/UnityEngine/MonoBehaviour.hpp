#pragma once
#include "Object.hpp"

namespace YimMenu
{
    class UnityEngine_Component_Fields : public UnityEngine_Object_Fields
    { };

    class UnityEngine_Behaviour_Fields : public UnityEngine_Component_Fields
    { };

    class UnityEngine_MonoBehaviour_Fields : public UnityEngine_Behaviour_Fields
    { };
}
