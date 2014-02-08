#include "math/matrix_math.h"
#include <iostream>

#define IS_TRUE(statement) \
	cout << #statement << "? " << ((statement)?"True.":"False.") << endl;

using namespace std;

int main(int argc, char** argv) {
	using namespace matrix_math;
	vec3 vec1(0.0f, 1.0f, 1.0f);
	vec3 vec2(1.0f, 2.0f, 2.0f);
	vec3 res(1.0f, 3.0f, 3.0f);
	IS_TRUE((vec1 + vec2) == res );
	float a[9] = {  1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f
				 };

	float b[9] = {  1.0f, 0.0f, 0.0f,
					1.0f, 0.0f, 0.0f,
					2.0f, 0.0f, 0.0f};

	float v[3] = {1.0f, 1.0f, 1.0f};
	vec3 vec(v);
	mat3 mat1(a);
	mat3 mat2(b);

	IS_TRUE((mat2 * mat1) == mat2);
	IS_TRUE((mat1 * mat2) == mat2);
	IS_TRUE((mat1 * vec) == vec);
}
