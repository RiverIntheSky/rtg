#pragma once

/// Include this header whenever you need access to OpenGL functions

#include "glad/glad.h"

namespace glow
{
/**
 * @brief restores various openGL states to their default setting
 *
 * This is not necessarily comprehensive, so better check the implementation to be sure
 *
 * Includes at least:
 *   * all glEnable/Disable states
 *   * their derived calls (glBlendFunc, ...)
 */
void restoreDefaultOpenGLState();
}
