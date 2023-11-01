#pragma once
#include"Matrix4x4.h"
#include"Transform.h"
#include"Multiply.h"

Matrix4x4  MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 A = {};

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	A.m[0][0] = scale.x * rotateXYZMatrix.m[0][0];
	A.m[0][1] = scale.x * rotateXYZMatrix.m[0][1];
	A.m[0][2] = scale.x * rotateXYZMatrix.m[0][2];
	A.m[0][3] = 0.0f;

	A.m[1][0] = scale.y * rotateXYZMatrix.m[1][0];
	A.m[1][1] = scale.y * rotateXYZMatrix.m[1][1];
	A.m[1][2] = scale.y * rotateXYZMatrix.m[1][2];
	A.m[1][3] = 0.0f;

	A.m[2][0] = scale.z * rotateXYZMatrix.m[2][0];
	A.m[2][1] = scale.z * rotateXYZMatrix.m[2][1];
	A.m[2][2] = scale.z * rotateXYZMatrix.m[2][2];
	A.m[2][3] = 0.0f;

	A.m[3][0] = translate.x;
	A.m[3][1] = translate.y;
	A.m[3][2] = translate.z;
	A.m[3][3] = 1.0f;
	return A;


}