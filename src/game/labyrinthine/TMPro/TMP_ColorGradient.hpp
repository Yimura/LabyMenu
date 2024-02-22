#pragma once
#include "../UnityEngine/Color.hpp"
#include "../UnityEngine/ScriptableObject.hpp"

#include <cstdint>

namespace YimMenu
{
    class TMP_ColorGradient_Fields : public UnityEngine_ScriptableObject_Fields
    {
        int32_t colorMode;
        Color topLeft;
        Color topRight;
        Color bottomLeft;
        Color bottomRight;
    };

	struct TMP_ColorGradient_o
	{
		void* klass;
		void* monitor;
		TMP_ColorGradient_Fields fields;
	};
}
