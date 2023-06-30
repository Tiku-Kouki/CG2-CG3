#pragma once
#include"Matrix4x4.h"

Matrix4x4 MakeIdentity4x4() {

	Matrix4x4 A = {};
	A.m[0][0] = 1.0f;
	A.m[0][1] = 0.0f;
	A.m[0][2] = 0.0f;
	A.m[0][3] = 0.0f;

	A.m[1][0] = 0.0f;
	A.m[1][1] = 1.0f;
	A.m[1][2] = 0.0f;
	A.m[1][3] = 0.0f;

	A.m[2][0] = 0.0f;
	A.m[2][1] = 0.0f;
	A.m[2][2] = 1.0f;
	A.m[2][3] = 0.0f;

	A.m[3][0] = 0.0f;
	A.m[3][1] = 0.0f;
	A.m[3][2] = 0.0f;
	A.m[3][3] = 1.0f;

	return A;



}