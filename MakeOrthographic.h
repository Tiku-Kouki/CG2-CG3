#pragma once
#include "Matrix4x4.h"

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {

	Matrix4x4 A;

	A.m[0][0] = 2.0f / (right - left);
	A.m[0][1] = 0.0f;
	A.m[0][2] = 0.0f;
	A.m[0][3] = 0.0f;

	A.m[1][0] = 0.0f;
	A.m[1][1] = 2.0f / (top - bottom);
	A.m[1][2] = 0.0f;
	A.m[1][3] = 0.0f;

	A.m[2][0] = 0.0f;
	A.m[2][1] = 0.0f;
	A.m[2][2] = 1.0f / (farClip - nearClip);
	A.m[2][3] = 0.0f;

	A.m[3][0] = (left + right) / (left - right);
	A.m[3][1] = (top + bottom) / (bottom - top);
	A.m[3][2] = nearClip / (nearClip - farClip);
	A.m[3][3] = 1.0f;

	return A;


}

