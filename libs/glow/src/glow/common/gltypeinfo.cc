#include "gltypeinfo.hh"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>

#include <cstdint>

namespace glow
{
// ==========================================================
// C++ Types
template <>
GLenum glTypeOf<int8_t>::type = GL_BYTE;
template <>
GLenum glTypeOf<int8_t>::format = GL_RED_INTEGER;
template <>
GLint glTypeOf<int8_t>::size = 1;

template <>
GLenum glTypeOf<uint8_t>::type = GL_UNSIGNED_BYTE;
template <>
GLenum glTypeOf<uint8_t>::format = GL_RED;
template <>
GLint glTypeOf<uint8_t>::size = 1;

template <>
GLenum glTypeOf<int16_t>::type = GL_SHORT;
template <>
GLenum glTypeOf<int16_t>::format = GL_RED_INTEGER;
template <>
GLint glTypeOf<int16_t>::size = 1;

template <>
GLenum glTypeOf<uint16_t>::type = GL_UNSIGNED_SHORT;
template <>
GLenum glTypeOf<uint16_t>::format = GL_RED_INTEGER;
template <>
GLint glTypeOf<uint16_t>::size = 1;

template <>
GLenum glTypeOf<int32_t>::type = GL_INT;
template <>
GLenum glTypeOf<int32_t>::format = GL_RED_INTEGER;
template <>
GLint glTypeOf<int32_t>::size = 1;
template <>
internal::glBaseType glTypeOf<int32_t>::basetype = internal::glBaseType::Int;

template <>
GLenum glTypeOf<uint32_t>::type = GL_UNSIGNED_INT;
template <>
GLenum glTypeOf<uint32_t>::format = GL_RED_INTEGER;
template <>
GLint glTypeOf<uint32_t>::size = 1;
template <>
internal::glBaseType glTypeOf<uint32_t>::basetype = internal::glBaseType::UInt;

template <>
GLenum glTypeOf<float>::type = GL_FLOAT;
template <>
GLenum glTypeOf<float>::format = GL_RED;
template <>
GLint glTypeOf<float>::size = 1;
template <>
internal::glBaseType glTypeOf<float>::basetype = internal::glBaseType::Float;

template <>
GLenum glTypeOf<double>::type = GL_DOUBLE;
template <>
GLint glTypeOf<double>::size = 1;
template <>
internal::glBaseType glTypeOf<double>::basetype = internal::glBaseType::Double;


// ==========================================================
// GLM Types
template <>
GLenum glTypeOf<glm::vec2>::type = GL_FLOAT;
template <>
GLenum glTypeOf<glm::vec2>::format = GL_RG;
template <>
GLint glTypeOf<glm::vec2>::size = 2;
template <>
internal::glBaseType glTypeOf<glm::vec2>::basetype = internal::glBaseType::Float;

template <>
GLenum glTypeOf<glm::vec3>::type = GL_FLOAT;
template <>
GLenum glTypeOf<glm::vec3>::format = GL_RGB;
template <>
GLint glTypeOf<glm::vec3>::size = 3;
template <>
internal::glBaseType glTypeOf<glm::vec3>::basetype = internal::glBaseType::Float;

template <>
GLenum glTypeOf<glm::vec4>::type = GL_FLOAT;
template <>
GLenum glTypeOf<glm::vec4>::format = GL_RGBA;
template <>
GLint glTypeOf<glm::vec4>::size = 4;
template <>
internal::glBaseType glTypeOf<glm::vec4>::basetype = internal::glBaseType::Float;


template <>
GLenum glTypeOf<glm::ivec2>::type = GL_INT;
template <>
GLenum glTypeOf<glm::ivec2>::format = GL_RG_INTEGER;
template <>
GLint glTypeOf<glm::ivec2>::size = 2;
template <>
internal::glBaseType glTypeOf<glm::ivec2>::basetype = internal::glBaseType::Int;

template <>
GLenum glTypeOf<glm::ivec3>::type = GL_INT;
template <>
GLenum glTypeOf<glm::ivec3>::format = GL_RGB_INTEGER;
template <>
GLint glTypeOf<glm::ivec3>::size = 3;
template <>
internal::glBaseType glTypeOf<glm::ivec3>::basetype = internal::glBaseType::Int;

template <>
GLenum glTypeOf<glm::ivec4>::type = GL_INT;
template <>
GLenum glTypeOf<glm::ivec4>::format = GL_RGBA_INTEGER;
template <>
GLint glTypeOf<glm::ivec4>::size = 4;
template <>
internal::glBaseType glTypeOf<glm::ivec4>::basetype = internal::glBaseType::Int;


template <>
GLenum glTypeOf<glm::uvec2>::type = GL_UNSIGNED_INT;
template <>
GLenum glTypeOf<glm::uvec2>::format = GL_RG_INTEGER;
template <>
GLint glTypeOf<glm::uvec2>::size = 2;
template <>
internal::glBaseType glTypeOf<glm::uvec2>::basetype = internal::glBaseType::UInt;

template <>
GLenum glTypeOf<glm::uvec3>::type = GL_UNSIGNED_INT;
template <>
GLenum glTypeOf<glm::uvec3>::format = GL_RGB_INTEGER;
template <>
GLint glTypeOf<glm::uvec3>::size = 3;
template <>
internal::glBaseType glTypeOf<glm::uvec3>::basetype = internal::glBaseType::UInt;

template <>
GLenum glTypeOf<glm::uvec4>::type = GL_UNSIGNED_INT;
template <>
GLenum glTypeOf<glm::uvec4>::format = GL_RGBA_INTEGER;
template <>
GLint glTypeOf<glm::uvec4>::size = 4;
template <>
internal::glBaseType glTypeOf<glm::uvec4>::basetype = internal::glBaseType::UInt;


template <>
GLenum glTypeOf<glm::dvec2>::type = GL_DOUBLE;
template <>
GLint glTypeOf<glm::dvec2>::size = 2;
template <>
internal::glBaseType glTypeOf<glm::dvec2>::basetype = internal::glBaseType::Double;

template <>
GLenum glTypeOf<glm::dvec3>::type = GL_DOUBLE;
template <>
GLint glTypeOf<glm::dvec3>::size = 3;
template <>
internal::glBaseType glTypeOf<glm::dvec3>::basetype = internal::glBaseType::Double;

template <>
GLenum glTypeOf<glm::dvec4>::type = GL_DOUBLE;
template <>
GLint glTypeOf<glm::dvec4>::size = 4;
template <>
internal::glBaseType glTypeOf<glm::dvec4>::basetype = internal::glBaseType::Double;


template <>
internal::glBaseType glTypeOf<glm::mat2x2>::basetype = internal::glBaseType::Float;
template <>
internal::glBaseType glTypeOf<glm::mat2x3>::basetype = internal::glBaseType::Float;
template <>
internal::glBaseType glTypeOf<glm::mat2x4>::basetype = internal::glBaseType::Float;
template <>
internal::glBaseType glTypeOf<glm::mat3x2>::basetype = internal::glBaseType::Float;
template <>
internal::glBaseType glTypeOf<glm::mat3x3>::basetype = internal::glBaseType::Float;
template <>
internal::glBaseType glTypeOf<glm::mat3x4>::basetype = internal::glBaseType::Float;
template <>
internal::glBaseType glTypeOf<glm::mat4x2>::basetype = internal::glBaseType::Float;
template <>
internal::glBaseType glTypeOf<glm::mat4x3>::basetype = internal::glBaseType::Float;
template <>
internal::glBaseType glTypeOf<glm::mat4x4>::basetype = internal::glBaseType::Float;

template <>
internal::glBaseType glTypeOf<glm::dmat2x2>::basetype = internal::glBaseType::Double;
template <>
internal::glBaseType glTypeOf<glm::dmat2x3>::basetype = internal::glBaseType::Double;
template <>
internal::glBaseType glTypeOf<glm::dmat2x4>::basetype = internal::glBaseType::Double;
template <>
internal::glBaseType glTypeOf<glm::dmat3x2>::basetype = internal::glBaseType::Double;
template <>
internal::glBaseType glTypeOf<glm::dmat3x3>::basetype = internal::glBaseType::Double;
template <>
internal::glBaseType glTypeOf<glm::dmat3x4>::basetype = internal::glBaseType::Double;
template <>
internal::glBaseType glTypeOf<glm::dmat4x2>::basetype = internal::glBaseType::Double;
template <>
internal::glBaseType glTypeOf<glm::dmat4x3>::basetype = internal::glBaseType::Double;
template <>
internal::glBaseType glTypeOf<glm::dmat4x4>::basetype = internal::glBaseType::Double;
}
