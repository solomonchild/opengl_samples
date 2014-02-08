#include "math/matrix_math.h"
#ifdef WIN32
#include "mem.h"
#endif

#include <assert.h>
#include "math/common_impl.h"

namespace matrix_math {

vec3::vec3(const vec2& vec, float z) {
	memcpy(v, vec.v, sizeof(vec.v));
	v[2] = z;
}

vec3::vec3(float a[3]) {
	memcpy(v, a, sizeof(v));
}

vec3::vec3(const vec3& vec) {
	memcpy(v, vec.v, sizeof(v));
}

vec3& vec3::operator =(const vec3& vec) {
	memcpy(v, vec.v, sizeof(v));
	return *this;
}

vec3::vec3(float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

const vec3& vec3::operator +(const vec3& rhs) {
	impl::sum(v, rhs.v);
	return *this;
}
const vec3& vec3::operator -(const vec3& rhs) {
	impl::sub(v, rhs.v);
	return *this;
}
const vec3& vec3::operator *(float num) {
	impl::mul(v, num);
	return *this;
}
const vec3& vec3::operator +(float num) {
	impl::sum(v, num);
	return *this;
}
const vec3& vec3::operator -(float num) {
	impl::div(v, num);
	return *this;
}

bool vec3::operator ==(const vec3& vec) const {
	return impl::are_equal(v, vec.v);
}

}
