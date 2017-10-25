#include "Buffer.hh"

#include "glow/glow.hh"

#include <limits>
#include <cassert>

using namespace glow;

Buffer::Buffer(GLenum bufferType, const SharedBuffer &originalBuffer)
  : mType(bufferType), mOriginalBuffer(originalBuffer)
{
    checkValidGLOW();

    if (isAliasedBuffer())
    {
        if (mOriginalBuffer->isAliasedBuffer()) // follow alias chain
        {
            mOriginalBuffer = mOriginalBuffer->getOriginalBuffer();
            assert(!mOriginalBuffer->isAliasedBuffer());
        }

        mObjectName = mOriginalBuffer->getObjectName();
    }
    else
    {
        mObjectName = std::numeric_limits<decltype(mObjectName)>::max();
        glGenBuffers(1, &mObjectName);
        assert(mObjectName != std::numeric_limits<decltype(mObjectName)>::max() && "No OpenGL Context?");
    }
}

Buffer::~Buffer()
{
    if (!isAliasedBuffer())
    {
        checkValidGLOW();

        glDeleteBuffers(1, &mObjectName);
    }
}
