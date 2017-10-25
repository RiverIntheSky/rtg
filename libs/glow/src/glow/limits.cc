#include "limits.hh"

#include "glow.hh"

#include "gl.hh"

int glow::limits::maxCombinedTextureImageUnits = -1;
float glow::limits::maxAnisotropy = -1;

void glow::limits::update()
{
    checkValidGLOW();

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits);
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
}
