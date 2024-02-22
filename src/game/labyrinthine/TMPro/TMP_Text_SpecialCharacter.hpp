#pragma once
#include <cstdint>

namespace YimMenu
{
    struct TMP_Text_SpecialCharacter
    {
        struct TMPro_TMP_Character_o *character;
        struct TMPro_TMP_FontAsset_o *fontAsset;
        struct UnityEngine_Material_o *material;
        int32_t materialIndex;
    };
}
