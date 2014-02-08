#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "stddef.h"
#include <iostream>

namespace matrix_math
{


class vec2
{
public:
	friend class vec3;
	friend class vec4;
	vec2() {};
	vec2(float x, float y);
	vec2(const vec2& vec);
	float x() const { return v[0]; }
	float y() const { return v[1]; }
	void set_x(float x) { v[0] = x; }
	void set_y(float y) { v[1] = y; }
	bool operator ==(const vec2& vec) const ;
	bool operator =(const vec2& vec);
protected:
	float v[2];
};

class vec3 : public vec2
{
public:
	friend class vec4;
	friend class mat3;
	vec3(float x, float y, float z);
	vec3(float a[3]);
	vec3(const vec3& vec);
	vec3(const vec2& vec, float z);
	vec3() {};
	const vec3& operator +(const vec3& rhs);
	const vec3& operator -(const vec3& rhs);
	const vec3& operator *(float num);
	const vec3& operator +(float num);
	const vec3& operator -(float num);
	bool operator ==(const vec3& vec) const;
	bool operator !=(const vec3& vec) const { return !operator ==(vec); }
	vec3& operator =(const vec3& vec);
	float z() const { return v[2]; }
	void set_z(float z) { v[2] = z; }
protected:
	float v[3];
};

class vec4 : public vec3
{
public:
	friend class mat4;
	vec4();
	vec4(float x, float y, float z, float w);
	vec4(const float a[4]);
	vec4(const vec4& vec);
	vec4(const vec3& vec, float w);
	vec4(const vec2& vec, float z, float w);
	const vec4& operator +(const vec4& rhs);
	const vec4& operator -(const vec4& rhs);
	const vec4& operator *(float num);
	const vec4& operator +(float num);
	const vec4& operator -(float num);
	bool operator ==(const vec4& vec) const;
	bool operator !=(const vec4& vec) const { return !operator ==(vec); }
	bool operator =(const vec4& vec);
	float w() const { return v[3]; }
	void set_w(float w) { v[3] = w;}
protected:
	float v[4];
};


/*
 * stored in column major form
 */
class mat3
{
public:
	mat3();
	mat3(const float (&a)[9]);
	float get(int m, int n) const;
	void set(int m, int n, float val);
	vec3& getCol(int m) const;
	mat3 operator *(const mat3& rhs);
	vec3 operator *(const vec3& rhs);
	mat3& operator =(const mat3& rhs);
	bool operator ==(const mat3& rhs);
protected:
	static const size_t VEC_DIM = 3;
	mutable vec3 v[VEC_DIM];
};

class mat4: mat3
{
public:
	mat4();
	mat4(const float (&a)[9]);
	float get(int m, int n);
	void set(int m, int n, float val);
	vec4& getCol(int n);
	mat4& operator *(const mat4& rhs);
	mat4& operator *(const vec4& rhs);
	mat4& operator =(const mat4& rhs);
	bool operator ==(const mat4& rhs);
protected:
	static const size_t VEC_DIM = 4;
	vec4 v[VEC_DIM];
};

}
#endif
