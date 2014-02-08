#include "math/matrix_math.h"
#ifdef WINVEC_DIM2
#include "mem.h"
#endif

#include <assert.h>
#include "math/common_impl.h"

namespace matrix_math {

mat3::mat3(const float (&a)[9])
{
	impl::copy_array_to_vec(v, VEC_DIM, a);
}

mat3::mat3()
{
	impl::init_array(v, VEC_DIM);
}

/*
 * m - row, n - column
 */
float mat3::get(int m, int n) const
{
	assert( m <= VEC_DIM);
	assert( n <= VEC_DIM);
	return v[m].v[n];
}

void mat3::set(int m, int n, float val) {
	v[m * VEC_DIM].v[n] = val;
}

vec3& mat3::getCol(int n) const

{
	assert( n <= VEC_DIM);
	return v[n];
}

mat3& mat3::operator =(const mat3& rhs)
{
	for(int i = 0; i < VEC_DIM; i++)
	{
		v[i] = rhs.v[i];
	}
	return *this;
}

mat3 mat3::operator *(const mat3& rhs)
{
	float a[VEC_DIM*VEC_DIM] = {0.0f};
	for(int i = 0; i < VEC_DIM; i++) {
		for(int j = 0; j < VEC_DIM; j++) {
			for(int z = 0; z < VEC_DIM; z++) {
				a[i * VEC_DIM + j] += v[i].v[z] * rhs.get(z , j);
			}
		}
	}
	return mat3(a);
}

vec3 mat3::operator *(const vec3& rhs) {
	float a[VEC_DIM] = {0.0f};
	for(int i = 0; i < VEC_DIM; i++) {
		for(int j = 0; j < VEC_DIM; j++) {
			a[i] += v[i].v[j] * rhs.v[j];
		}
	}
	return vec3(a);
}

bool mat3::operator ==(const mat3& rhs)
{
	for(int i = 0; i < VEC_DIM; i++)
	{
		if(v[i] != rhs.getCol(i))
			return false;
	}
	return true;
}
}
