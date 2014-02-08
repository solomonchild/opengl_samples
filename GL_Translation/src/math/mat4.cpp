#include "math/matrix_math.h"
#ifdef WIN32
#include "mem.h"
#endif

#include <assert.h>
#include "math/common_impl.h"

namespace matrix_math {
mat4::mat4() {
	 impl::init_array(v, VEC_DIM);
}
mat4::mat4(const float (&a)[9]) {
	impl::copy_array_to_vec(v, VEC_DIM, a);
}

float mat4::get(int m, int n) {
	return v[m].v[n];
}
void mat4::set(int m, int n, float val) {
	v[m * VEC_DIM].v[n] = val;
}
vec4& mat4::getCol(int n) {
	return v[n];
}
mat4& mat4::operator *(const mat4& rhs) {

}
mat4& mat4::operator *(const vec4& rhs) {

}
mat4& mat4::operator =(const mat4& rhs) {

}
bool mat4::operator ==(const mat4& rhs) {

}
}
