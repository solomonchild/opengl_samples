#ifndef COMMON_IMPL_H
#define COMMON_IMPL_H
#ifdef WIN32
#include "mem.h"
#endif
#include <stdint.h>

namespace matrix_math
{
namespace impl
{

template<typename T, size_t size>
void init_array(T (&arr)[size], int vecDim) {
	for(int i = 0; i < size / vecDim; i++) {
		memset(arr + i, 0, vecDim);
	}
}

template<typename T, size_t size, size_t size_from>
void copy_array_to_vec(T (&arr)[size], int vecDim, float const (&a)[size_from]) {

	assert(size * vecDim == size_from);
	float to[vecDim];
	for(int i = 0; i < vecDim; i++)
	{
		memcpy(to, a + i*vecDim, sizeof(float) * vecDim);
		T vec(to);
		arr[i] = vec;
	}
}

template<typename T, size_t size>
bool are_equal(T const (&first)[size], T const (&second)[size]) {
	for (int i = 0; i < size; i++) {
		if(first[i] != second[i])
			return false;
	}
	return true;
}
template<typename T, size_t size>
void sum(T (&dest)[size], const T (&source)[size]) {
	for (int i = 0; i < size; i++) {
		dest[i] += source[i];
	}
}

template<typename T, size_t size>
void sub(T (&dest)[size], const T (&source)[size]) {
	for (int i = 0; i < size; i++) {
		dest[i] -= source[i];
	}
}
template<typename T, size_t size>
void mul(T (&dest)[size], float num) {
	for (int i = 0; i < size; i++) {
		dest[i] *= num;
	}
}
template<typename T, size_t size>
void div(T (&dest)[size], float num) {
	for (int i = 0; i < size; i++) {
		dest[i] /= num;
	}
}

template<typename T, size_t size>
void sum(T (&dest)[size], float num) {
	for (int i = 0; i < size; i++) {
		dest[i] += num;
	}
}

template<typename T, size_t size>
void sub(T (&dest)[size], float num) {
	for (int i = 0; i < size; i++) {
		dest[i] -= num;
	}
}
}
}
#endif
