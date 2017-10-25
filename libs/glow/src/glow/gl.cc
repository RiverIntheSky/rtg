#include "gl.hh"

#include "glow.hh"

void glow::restoreDefaultOpenGLState()
{
    checkValidGLOW();

    // The initial value for each capability with the exception of GL_DITHER and GL_MULTISAMPLE is GL_FALSE.
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_LOGIC_OP);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEBUG_OUTPUT);
    glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDisable(GL_DEPTH_CLAMP);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FRAMEBUFFER_SRGB);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_POLYGON_OFFSET_POINT);
    glDisable(GL_POLYGON_SMOOTH);
    glDisable(GL_PRIMITIVE_RESTART);
    glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    glDisable(GL_RASTERIZER_DISCARD);
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glDisable(GL_SAMPLE_ALPHA_TO_ONE);
    glDisable(GL_SAMPLE_COVERAGE);
#if GLOW_OPENGL_VERSION >= 40
    glDisable(GL_SAMPLE_SHADING);
#endif
    glDisable(GL_SAMPLE_MASK);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDisable(GL_PROGRAM_POINT_SIZE);

    // The initial value for GL_DITHER and GL_MULTISAMPLE is GL_TRUE.
    glEnable(GL_DITHER);
    glEnable(GL_MULTISAMPLE);

    // clear
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // blending
    glBlendFunc(GL_ONE, GL_ZERO);
    glBlendColor(0.f, 0.f, 0.f, 0.f);
    glBlendEquation(GL_FUNC_ADD);

    // logic op
    glLogicOp(GL_COPY);

    // depth test
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
    glDepthRange(0.0, 1.0);

    // culling
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // point/line width
    glLineWidth(1.f);
    glPointSize(1.f);

    // sample cov
    glSampleCoverage(1.f, GL_FALSE);

    // poly offset
    glPolygonOffset(0.f, 0.f);

    // prim restart (has no default)
    // glPrimitiveRestartIndex()

    // stencil test
    glStencilFunc(GL_ALWAYS, 0, 0xFFffFFff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // default pixel store
    glPixelStorei(GL_PACK_SWAP_BYTES, false);
    glPixelStorei(GL_PACK_LSB_FIRST, false);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_IMAGE_HEIGHT, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_PACK_SKIP_IMAGES, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);

    glPixelStorei(GL_UNPACK_SWAP_BYTES, false);
    glPixelStorei(GL_UNPACK_LSB_FIRST, false);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_IMAGES, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    // seamless cubemap filtering
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
