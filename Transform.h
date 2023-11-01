#pragma once
#include"Vector3.h"
#include"Matrix4x4.h"
#include<stdlib.h>
#include<cmath>
#include <cassert>

struct Transform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;

};

Vector3 Add(const Vector3& m1, const Vector3& m2) {
	Vector3 A = {};

	A.x = m1.x + m2.x;
	A.y = m1.y + m2.y;
	A.z = m1.z + m2.z;

	return A;
}


Matrix4x4 MakeRotateXMatrix(float theta) {
	Matrix4x4 A = {};

	A.m[0][0] = 1.0f;
	A.m[0][1] = 0.0f;
	A.m[0][2] = 0.0f;
	A.m[0][3] = 0.0f;

	A.m[1][0] = 0.0f;
	A.m[1][1] = std::cos(theta);
	A.m[1][2] = std::sin(theta);
	A.m[1][3] = 0.0f;

	A.m[2][0] = 0.0f;
	A.m[2][1] = -std::sin(theta);
	A.m[2][2] = std::cos(theta);
	A.m[2][3] = 0.0f;

	A.m[3][0] = 0.0f;
	A.m[3][1] = 0.0f;
	A.m[3][2] = 0.0f;
	A.m[3][3] = 1.0f;

	return A;
}
Matrix4x4 MakeRotateYMatrix(float theta) {
	Matrix4x4 A = {};

	A.m[0][0] = std::cos(theta);
	A.m[0][1] = 0.0f;
	A.m[0][2] = -std::sin(theta);
	A.m[0][3] = 0.0f;

	A.m[1][0] = 0.0f;
	A.m[1][1] = 1.0f;
	A.m[1][2] = 0.0f;
	A.m[1][3] = 0.0f;

	A.m[2][0] = std::sin(theta);
	A.m[2][1] = 0.0f;
	A.m[2][2] = std::cos(theta);
	A.m[2][3] = 0.0f;

	A.m[3][0] = 0.0f;
	A.m[3][1] = 0.0f;
	A.m[3][2] = 0.0f;
	A.m[3][3] = 1.0f;

	return A;
}
Matrix4x4 MakeRotateZMatrix(float theta) {
	Matrix4x4 A = {};

	A.m[0][0] = std::cos(theta);
	A.m[0][1] = std::sin(theta);
	A.m[0][2] = 0.0f;
	A.m[0][3] = 0.0f;

	A.m[1][0] = -std::sin(theta);
	A.m[1][1] = std::cos(theta);
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
Matrix4x4 MakeTranslateMatrix(Vector3 translate)
{
	Matrix4x4 A = { 0 };

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

	A.m[3][0] = translate.x;
	A.m[3][1] = translate.y;
	A.m[3][2] = translate.z;
	A.m[3][3] = 1.0f;
	return A;
}

Matrix4x4 MakePerspectiveFoveMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {

	Matrix4x4 A = {};

	A.m[0][0] = (1.0f / aspectRatio) * (1 / (tanf(fovY / 2)));
	A.m[0][1] = 0.0f;
	A.m[0][2] = 0.0f;
	A.m[0][3] = 0.0f;

	A.m[1][0] = 0.0f;
	A.m[1][1] = 1 / (tanf(fovY / 2));
	A.m[1][2] = 0.0f;
	A.m[1][3] = 0.0f;

	A.m[2][0] = 0.0f;
	A.m[2][1] = 0.0f;
	A.m[2][2] = farClip / (farClip - nearClip);
	A.m[2][3] = 1.0f;

	A.m[3][0] = 0.0f;
	A.m[3][1] = 0.0f;
	A.m[3][2] = (- nearClip * farClip) / (farClip - nearClip);
	A.m[3][3] = 0.0f;

	return A;

}

Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 A = {};
	float determinant;
	determinant
		= +m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	assert(determinant != 0.0f);
	float determinantRecp = 1.0f / determinant;


	A.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) * determinantRecp;
	A.m[0][1] = (
		-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) * determinantRecp;
	A.m[0][2] = (
		m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) * determinantRecp;
	A.m[0][3] = (
		-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) * determinantRecp;

	A.m[1][0] = (
		-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
		+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) * determinantRecp;
	A.m[1][1] = (
		m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) * determinantRecp;
	A.m[1][2] = (
		-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
		+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) * determinantRecp;
	A.m[1][3] = (
		m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) * determinantRecp;

	A.m[2][0] = (
		m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) * determinantRecp;
	A.m[2][1] = -(
		m.m[0][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][1]
		- m.m[0][3] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][1]) * determinantRecp;
	A.m[2][2] = (
		m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) * determinantRecp;
	A.m[2][3] = -(
		m.m[0][0] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][1]
		- m.m[0][3] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][1]) * determinantRecp;

	A.m[3][0] = -(
		m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[1][1] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[1][0] * m.m[2][2] * m.m[3][1]) * determinantRecp;

	A.m[3][1] = (
		m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) * determinantRecp;
	A.m[3][2] = -(
		m.m[0][0] * m.m[1][1] * m.m[3][2] + m.m[0][1] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][2] - m.m[0][0] * m.m[1][2] * m.m[3][1]) * determinantRecp;
	A.m[3][3] = (
		m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) * determinantRecp;


	return A;
}
