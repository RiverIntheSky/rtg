#pragma once

namespace glow
{
/**
 * @brief Color space of a given texture
 */
enum class ColorSpace
{
    Linear,
    sRGB,

    // special color space which tries to automatically detect the correct space
    AutoDetect
};
}
