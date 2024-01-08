#pragma once
#include <cstdint>

namespace YimMenu
{
    struct TMP_FontStyleStack
    {
        uint8_t bold;
        uint8_t italic;
        uint8_t underline;
        uint8_t strikethrough;
        uint8_t highlight;
        uint8_t superscript;
        uint8_t subscript;
        uint8_t uppercase;
        uint8_t lowercase;
        uint8_t smallcaps;
    };
}
