#include "math/matrix_math.h"
#ifdef WIN32
#include "mem.h"
#endif

#include <assert.h>
#include "math/common_impl.h"

namespace matrix_math {

vec2::vec2(const vec2& vec) {
	memcpy(v, vec.v, sizeof(v));
}

vec2::vec2(float x, float y) {
	v[0] = x;
	v[1] = y;
}

bool vec2::operator ==(const vec2& vec) const {
	return impl::are_equal(v, vec.v);
}


}
