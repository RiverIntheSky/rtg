#pragma once

#include "glow/common/shared.hh"
#include "glow/common/non_copyable.hh"
#include "glow/common/property.hh"

#include "glow/gl.hh"

#include <vector>

namespace glow
{
/**
 * @brief Container for a single continuous data layer of a texture
 *
 * Can be arbitrary rectangular subdata
 *
 * E.g. cube maps have 6 surfaces at mipmap level 0
 */
GLOW_SHARED(class, SurfaceData);
GLOW_SHARED(class, TextureData);
class SurfaceData
{
    GLOW_NON_COPYABLE(SurfaceData);

private:
    int mMipmapLevel = 0;

    size_t mOffsetX = 0;
    size_t mOffsetY = 0;
    size_t mOffsetZ = 0;

    size_t mWidth = 1;
    size_t mHeight = 1;
    size_t mDepth = 1;

    GLenum mFormat;
    GLenum mType;

    /// special target for cubemaps
    GLenum mTarget = GL_INVALID_ENUM;

    std::vector<char> mData;

public: // getter, setter
    GLOW_PROPERTY(Width);
    GLOW_PROPERTY(Height);
    GLOW_PROPERTY(Depth);

    GLOW_PROPERTY(OffsetX);
    GLOW_PROPERTY(OffsetY);
    GLOW_PROPERTY(OffsetZ);

    size_t getSize() const { return mWidth * mHeight * mDepth; }
    GLOW_PROPERTY(Format);
    GLOW_PROPERTY(Type);

    GLOW_PROPERTY(Target);

    GLOW_PROPERTY(MipmapLevel);

    GLOW_PROPERTY(Data);

public:
    SurfaceData();

    /// Returns a copy of this data, which only contains a given range
    /// The specified range must be within the current surface
    /// Respects any offset that is already present (x, y, z are RELATIVE to current surface data, e.g. x must always be in [0, width - 1])
    SharedSurfaceData getSubData(size_t x, size_t y, size_t z, size_t width, size_t height, size_t depth) const;

    /// Makes a texture data using a COPY of this data
    /// Ignores offset, ignores mipmap level, has no proper internal format and tex parameters
    ///
    /// Note: useful for saving a single surface layer
    SharedTextureData makeTextureData() const;

    /// Converts this surface data to a given format
    ///
    /// Note: this is implemented via uploading to a 3D texture and downloading again (requires OGL)
    /// Caution: may not work with integer internal formats
    SharedSurfaceData convertTo(GLenum format, GLenum type = GL_UNSIGNED_BYTE) const;
};
}
