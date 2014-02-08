#include "math/matrix_math.h"
#ifdef WIN32
#include "mem.h"
#endif

#include <assert.h>
#include "math/common_impl.h"

namespace matrix_math {

vec4::vec4() {
	impl::init_array(v, 4);
}

vec4::vec4(const float a[4]) {
	memcpy(v, a, 4);
}

vec4::vec4(float x, float y, float z, float w) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;

}

bool vec4::operator =(const vec4& vec) {
	memcpy(v, vec.v, sizeof(v));
}

vec4::vec4(const vec4& vec) {
	memcpy(v, vec.v, sizeof(v));
}
vec4::vec4(const vec3& vec, float w) {
	memcpy(v, vec.v, sizeof(vec));
	v[3] = w;

}
vec4::vec4(const vec2& vec, float z, float w) {
	memcpy(v, vec.v, sizeof(vec.v));
	v[3] = w;

}
const vec4& vec4::operator +(const vec4& rhs) {
	impl::sum(v, rhs.v);
	return *this;
}
const vec4& vec4::operator -(const vec4& rhs) {
	impl::sub(v, rhs.v);
	return *this;
}
const vec4& vec4::operator *(float num) {
	impl::mul(v, num);
	return *this;
}
const vec4& vec4::operator +(float num) {
	impl::sum(v, num);
	return *this;
}
const vec4& vec4::operator -(float num) {
	impl::sub(v, num);
	return *this;
}

bool vec4::operator ==(const vec4& vec) const {
	return impl::are_equal(v, vec.v);
}

}
