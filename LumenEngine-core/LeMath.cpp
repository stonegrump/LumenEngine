#include "LeMath.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vec3.h"
#include "Vec4.h"
#include <cmath>



Vec3 * LeMath::CreateReflectionVec3(const Vec3 & in, const Vec3 & normal)
{
	return new Vec3(in - normal * (2.f * Dot(in, normal)));
}

Vec3 * LeMath::CreateRefractionVec3(const Vec3 & in, const Vec3 & normal, float indexOfRefraction)
{
	float d = Dot(in, normal);
	float k = 1 - indexOfRefraction * indexOfRefraction * (1 - d * d);

	if (k < 0)
		return new Vec3(0, 0, 0);
	else
		return new Vec3(in * indexOfRefraction - normal * (indexOfRefraction * Dot(in, normal) + sqrt(k)));
}

float LeMath::Lerp(float a, float b, float t)
{
	return a + ((t < 0) ? 0 : (t > 1) ? 1 : t) * (b - a);
}

float LeMath::QuadraticBezierLerp(float begin, float mid, float end, float t)
{
	return begin + (2 * t * (mid - begin)) + ((t * t) * (end - (2 * mid) + begin));
}

float LeMath::CubicBezierLerp(float begin, float mid, float mid2, float end, float t)
{
	return QuadraticBezierLerp(Lerp(begin, mid, t), Lerp(mid, mid2, t), Lerp(mid2, end, t), t);
}

float LeMath::CubicBSpline(float cp[10], float t)
{
	float f = t * 3.0f;
	int i = int(floor(f));
	float s = t - (int)t;

	if (t <= 0)
		return cp[0];
	else if (t >= 1)
		return cp[9];

	return CubicBezierLerp(cp[i * 3], cp[i * 3 + 1], cp[i * 3 + 2], cp[i * 3 + 3], s);
}

float LeMath::Dot(const Vec3 & a, const Vec3 & b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float LeMath::Angle(const Vec3 & a, const Vec3 & b)
{
	return acos(Dot(a, b));
}

Vec3 LeMath::Cross(const Vec3 & a, const Vec3 & b)
{
	return Vec3((a.y * b.z) - (b.y * a.z), (b.x * a.z) - (a.x * b.z), (a.x * b.y) - (b.x * a.y));
}

Vec3 * LeMath::PCross(const Vec3 * const a, const Vec3 * const b)
{
	return new Vec3((a->y * b->z) - (b->y * a->z), (a->x * b->z) - (b->x * a->z), (a->x * b->y) - (b->x * a->y));
}

float LeMath::Length(const Vec3 & vec)
{
	return  sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

Vec3 * LeMath::GetNormalizedVector(const Vec3 & vec)
{
	return new Vec3(vec / Length(vec));
}

Matrix3x3 *LeMath::CreateSkewMatrix(const Vec3 & other)
{
	return new Matrix3x3(0, -other.z, other.y,
		other.z, 0, -other.x,
		-other.y, other.x, 0);
}

#pragma region GetMatrixXX

float LeMath::DegreesToRadians(float angleInDegrees)
{
	return angleInDegrees * ((float)LePI / 180.f);
}

Matrix3x3 * LeMath::GetTransposeMatrix3x3(const Matrix3x3 & original)
{
	Matrix3x3 *rMat = new Matrix3x3(original);
	rMat->Transpose();
	return rMat;
}

Matrix4x4 * LeMath::GetTransposeMatrix4x4(const Matrix4x4 & original)
{
	Matrix4x4 *rMat = new Matrix4x4(original);
	rMat->Transpose();
	return rMat;
}

Matrix3x3 * LeMath::GetAdjointMatrix3x3(const Matrix3x3 & original)
{
	Matrix3x3 *rMat = new Matrix3x3(original);
	rMat->Adjoint();
	return rMat;
}

Matrix4x4 * LeMath::GetAdjointMatrix4x4(const Matrix4x4 & original)
{
	Matrix4x4 *rMat = new Matrix4x4(original);
	rMat->Adjoint();
	return rMat;
}

Matrix3x3 * LeMath::GetInverseMatrix3x3(const Matrix3x3 & original)
{
	Matrix3x3 *rMat = new Matrix3x3(original);
	rMat->Invert();
	return rMat;
}

Matrix4x4 * LeMath::GetInverseMatrix4x4(const Matrix4x4 & original)
{
	Matrix4x4 *rMat = new Matrix4x4(original);
	return rMat;
}

#pragma endregion

#pragma region CreateMatrixXX

#pragma region PointerReturnVersions
Matrix4x4 * LeMath::CreateScaleMatrixP(float x, float y, float z)
{
	return new Matrix4x4(x, 0, 0, 0,
						 0, y, 0, 0,
						 0, 0, z, 0,
						 0, 0, 0, 1);
}

Matrix4x4 * LeMath::CreateScaleMatrixP(const Vec3 & v)
{
	return new Matrix4x4(v.x, 0, 0, 0,
						 0, v.y, 0, 0,
						 0, 0, v.z, 0,
						 0, 0, 0, 1);
}

Matrix4x4 * LeMath::CreateScaleMatrixP(float a)
{
	return new Matrix4x4(a, 0, 0, 0,
		0, a, 0, 0,
		0, 0, a, 0,
		0, 0, 0, 1);
}

Matrix4x4 * LeMath::CreateRotationMatrixP(EAxis axis, float angle)
{
	switch (axis)
	{
	case x:
		return new Matrix4x4(1, 0, 0, 0,
			0, cos(angle), sin(angle), 0,
			0, -sin(angle), cos(angle), 0,
			0, 0, 0, 1);
	case y:
		return new Matrix4x4(cos(angle), 0, -sin(angle), 0,
							 0, 1, 0, 0,
							 sin(angle), 0, cos(angle), 0,
							 0, 0, 0, 1);
	case z:
		return new Matrix4x4(cos(angle), -sin(angle), 0.f, 0.f,
							 sin(angle), cos(angle), 0.f, 0.f,
							 0.f, 0.f, 1.f, 0.f,
							 0.f, 0.f, 0.f, 1.f);
	}
	return nullptr;
}

Matrix4x4 * LeMath::CreateRotationMatrixP(float x, float y, float z)
{
	return new Matrix4x4(cos(y) * cos(z),			cos(x) * sin(z) + sin(x) * sin(y) * cos(z), sin(x) * sin(z) - cos(x) * sin(y) * cos(z), 0.f,
						-cos(y) * sin(z),			cos(x) * cos(z) - sin(x) * sin(y) * sin(z), sin(x) * cos(z) + cos(x) * sin(y) * sin(z), 0.f,
						 sin(y),				   -sin(x) * cos(y),						    cos(x) * cos(y),							0.f,
						 0.f,						0.f,										0.f,										1.f);
}

Matrix4x4 * LeMath::CreateRotationMatrixP(float angle, const Vec3 &base)
{
	Matrix3x3 *temp = CreateSkewMatrix(base);
	Matrix4x4 *returnMat = new Matrix4x4(Matrix4x4::Identity() + (*temp) * sin(angle) + ((*temp) * (*temp)) * (1 - cos(angle)));
	delete temp;
	return returnMat;
}

Matrix4x4 * LeMath::CreateTranslationMatrixP(float x, float y, float z)
{
	return new Matrix4x4(1, 0, 0, x,
						 0, 1, 0, y,
						 0, 0, 1, z,
						 0, 0, 0, 1);
}

Matrix4x4 * LeMath::CreateTranslationMatrixP(const Vec3 & v)
{
	return new Matrix4x4(1, 0, 0, v.x,
						 0, 1, 0, v.y,
						 0, 0, 1, v.z,

						 0, 0, 0, 1);
}
#pragma endregion

#pragma region ConstReturnVersions
Matrix4x4 LeMath::CreateScaleMatrix(float x, float y, float z)
{
	return  Matrix4x4(x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

Matrix4x4 LeMath::CreateScaleMatrix(const Vec3 & v)
{
	return  Matrix4x4(v.x, 0, 0, 0,
		0, v.y, 0, 0,
		0, 0, v.z, 0,
		0, 0, 0, 1);
}

Matrix4x4 LeMath::CreateScaleMatrix(float a)
{
	return  Matrix4x4(a, 0, 0, 0,
		0, a, 0, 0,
		0, 0, a, 0,
		0, 0, 0, 1);
}

Matrix4x4 LeMath::CreateRotationMatrix(EAxis axis, float angle)
{
	switch (axis)
	{
	case x:
		return  Matrix4x4(1, 0, 0, 0,
			0, cos(angle), sin(angle), 0,
			0, -sin(angle), cos(angle), 0,
			0, 0, 0, 1);
	case y:
		return  Matrix4x4(cos(angle), 0, -sin(angle), 0,
			0, 1, 0, 0,
			sin(angle), 0, cos(angle), 0,
			0, 0, 0, 1);
	case z:
		return  Matrix4x4(cos(angle), -sin(angle), 0.f, 0.f,
			sin(angle), cos(angle), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
	}
	return Matrix4x4();
}

Matrix4x4 LeMath::CreateRotationMatrix(float x, float y, float z)
{
	return  Matrix4x4(cos(y) * cos(z), cos(x) * sin(z) + sin(x) * sin(y) * cos(z), sin(x) * sin(z) - cos(x) * sin(y) * cos(z), 0.f,
		-cos(y) * sin(z), cos(x) * cos(z) - sin(x) * sin(y) * sin(z), sin(x) * cos(z) + cos(x) * sin(y) * sin(z), 0.f,
		sin(y), -sin(x) * cos(y), cos(x) * cos(y), 0.f,
		0.f, 0.f, 0.f, 1.f);
}

Matrix4x4 LeMath::CreateRotationMatrix(float angle, const Vec3 &base)
{
	Matrix3x3 *temp = CreateSkewMatrix(base);
	Matrix4x4 returnMat =  Matrix4x4(Matrix4x4::Identity() + (*temp) * sin(angle) + ((*temp) * (*temp)) * (1 - cos(angle)));
	delete temp;
	return returnMat;
}

Matrix4x4 LeMath::CreateTranslationMatrix(float x, float y, float z)
{
	return  Matrix4x4(1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);
}

Matrix4x4 LeMath::CreateTranslationMatrix(const Vec3 & v)
{
	return  Matrix4x4(1, 0, 0, v.x,
		0, 1, 0, v.y,
		0, 0, 1, v.z,

		0, 0, 0, 1);
}
#pragma endregion

#pragma region OutMatVersions
void LeMath::CreateScaleMatrix(float x, float y, float z, Matrix4x4 * outMat)
{
	outMat->Set(x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

void LeMath::CreateScaleMatrix(const Vec3 & v, Matrix4x4 * outMat)
{
	outMat->Set(v.x, 0, 0, 0,
		0, v.y, 0, 0,
		0, 0, v.z, 0,
		0, 0, 0, 1);
}

void LeMath::CreateScaleMatrix(float a, Matrix4x4 * outMat)
{
	outMat->Set(a, 0, 0, 0,
		0, a, 0, 0,
		0, 0, a, 0,
		0, 0, 0, 1);
}

void LeMath::CreateRotationMatrix(EAxis axis, float angle, Matrix4x4 * outMat)
{
	switch (axis)
	{
	case x:
		outMat->Set(1, 0, 0, 0,
			0, cos(angle), sin(angle), 0,
			0, -sin(angle), cos(angle), 0,
			0, 0, 0, 1);
		break;
	case y:
		outMat->Set(cos(angle), 0, -sin(angle), 0,
			0, 1, 0, 0,
			sin(angle), 0, cos(angle), 0,
			0, 0, 0, 1);
		break;
	case z:
		outMat->Set(cos(angle), -sin(angle), 0.f, 0.f,
			sin(angle), cos(angle), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
		break;
	}
}

void LeMath::CreateRotationMatrix(float x, float y, float z, Matrix4x4 * outMat)
{
	outMat->Set(cos(y) * cos(z), cos(x) * sin(z) + sin(x) * sin(y) * cos(z), sin(x) * sin(z) - cos(x) * sin(y) * cos(z), 0.f,
		-cos(y) * sin(z), cos(x) * cos(z) - sin(x) * sin(y) * sin(z), sin(x) * cos(z) + cos(x) * sin(y) * sin(z), 0.f,
		sin(y), -sin(x) * cos(y), cos(x) * cos(y), 0.f,
		0.f, 0.f, 0.f, 1.f);
}

void LeMath::CreateRotationMatrix(float angle, const Vec3 & base, Matrix4x4 * outMat)
{
	Matrix3x3 *temp = CreateSkewMatrix(base);
	outMat->Set(Matrix4x4::Identity() + (*temp) * sin(angle) + ((*temp) * (*temp)) * (1 - cos(angle)));
	delete temp;
}

void LeMath::CreateTranslationMatrix(float x, float y, float z, Matrix4x4 * outMat)
{
	outMat->Set(1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);
}

void LeMath::CreateTranslationMatrix(const Vec3 & v, Matrix4x4 * outMat)
{
	outMat->Set(1, 0, 0, v.x,
		0, 1, 0, v.y,
		0, 0, 1, v.z,
		0, 0, 0, 1);
}
#pragma endregion

Matrix4x4 * LeMath::CreateLookAtMatrix(const Vec3 & eye, const Vec3 & point, const Vec3 & up)
{
	Vec3 forward = point - eye;
	forward.Normalize();
	Vec3 side = Cross(forward, up);
	Vec3 newUp = Cross(side, forward);
	return new Matrix4x4(Vec4(side.x, newUp.x, forward.x, -eye.x),
						 Vec4(side.y, newUp.y, forward.y, -eye.y),
						 Vec4(side.z, newUp.z, forward.z, -eye.z),
						 Vec4(0, 0, 0, 1));
}

Matrix4x4 * LeMath::CreateFrustumMatrix(float left, float right, float bottom, float top, float _near, float _far)
{
	return new Matrix4x4((2 * _near) / (right - left), 0, (right + left) / (right - left), 0,
		0, (2 * _near) / (top - bottom), (top + bottom) / (top - bottom), 0,
		0, 0, (_near + _far) / (_near - _far), (2 * _near*_far) / (_near - _far),
		0, 0, -1, 0);
}

Matrix4x4 * LeMath::CreatePerspectiveMatrix(float fov, float aspect, float _near, float _far)
{
	float q = 1.f / tan(DegreesToRadians(0.5f * fov));

	return new Matrix4x4(q / aspect, 0, 0, 0,
		0, q, 0, 0,
		0, 0, (_near + _far) / (_near - _far), -1,
		0, 0, (2 * _near * _far) / (_near - _far), 0);
}

Matrix4x4 *LeMath::CreateOrthoMatrix(float left, float right, float bottom, float top, float _near, float _far)
{
	return new Matrix4x4(2 / (right - left), 0, 0, (left + right) / (left - right),
		0, 2 / (top - bottom), 0, (bottom + top) / (bottom - top),
		0, 0, 2 / (_near - _far), (_near + _far)/(_far - _near),
		0, 0, 0, 1);
}

void LeMath::CreateFrustumMatrix(float left, float right, float bottom, float top, float _near, float _far, Matrix4x4 * outMat)
{
	outMat->Set((2 * _near) / (right - left), 0, (right + left) / (right - left), 0,
		0, (2 * _near) / (top - bottom), (top + bottom) / (top - bottom), 0,
		0, 0, (_near + _far) / (_near - _far), (2 * _near*_far) / (_near - _far),
		0, 0, -1, 0);
}

void LeMath::CreatePerspectiveMatrix(float fov, float aspect, float _near, float _far, Matrix4x4 * outMat)
{
	float q = 1.f / tan(DegreesToRadians(0.5f * fov));

	outMat->Set(q / aspect, 0, 0, 0,
		0, q, 0, 0,
		0, 0, (_near + _far) / (_near - _far), (2 * _near * _far) / (_near - _far),
		0, 0, -1, 0);
}

void LeMath::CreateOrthoMatrix(float left, float right, float bottom, float top, float _near, float _far, Matrix4x4 * outMat)
{
	outMat->Set(2 / (right - left), 0, 0, (left + right) / (left - right),
		0, 2 / (top - bottom), 0, (bottom + top) / (bottom - top),
		0, 0, 2 / (_near - _far), (_near + _far) / (_far - _near),
		0, 0, 0, 1);
}

void LeMath::CreateLookAtMatrix(const Vec3 & eye, const Vec3 & point, const Vec3 & up, Matrix4x4 * outMat)
{
	Vec3 forward = point - eye;
	forward.Normalize();
	Vec3 side = Cross(forward, up);
	Vec3 newUp = Cross(side, forward);
	outMat->Set(Vec4(side.x, newUp.x, forward.x, -eye.x),
		Vec4(side.y, newUp.y, forward.y, -eye.y),
		Vec4(side.z, newUp.z, forward.z, -eye.z),
		Vec4(0, 0, 0, 1));
}

#pragma endregion