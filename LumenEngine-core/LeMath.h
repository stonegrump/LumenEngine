#pragma once

#define LePI 3.14159265

class Matrix3x3;
class Matrix4x4;
class Vec3;

enum EAxis {
	x,
	y,
	z
};

class LeMath
{
public:
	static float DegreesToRadians(float angleInDegrees);

	//Returns a new matrix that is the transpose of the original without altering the original matrix.
	static Matrix3x3 *GetTransposeMatrix3x3(const Matrix3x3 &original);
	static Matrix4x4 *GetTransposeMatrix4x4(const Matrix4x4 &original);
	static Matrix3x3 *GetAdjointMatrix3x3(const Matrix3x3 &original);
	static Matrix4x4 *GetAdjointMatrix4x4(const Matrix4x4 &original);
	static Matrix3x3 *GetInverseMatrix3x3(const Matrix3x3 &original);
	static Matrix4x4 *GetInverseMatrix4x4(const Matrix4x4 &original);

	static Matrix4x4 *CreateScaleMatrix4x4(float x, float y, float z);
	static Matrix4x4 *CreateScaleMatrix4x4(const Vec3 &v);
	static Matrix4x4 *CreateScaleMatrix4x4(float a);
	static Matrix4x4 *CreateRotationMatrix4x4(EAxis axis, float angle);
	static Matrix4x4 *CreateRotationMatrix4x4(float x, float y, float z);
	static Matrix4x4 *CreateRotationMatrix4x4(float angle, const Vec3 &base);
	static Matrix4x4 *CreateTranslationMatrix4x4(float x, float y, float z);
	static Matrix4x4 *CreateTranslationMatrix4x4(const Vec3 &v);

	static Matrix4x4 *CreateLookAtMatrix(const Vec3 &eye, const Vec3 &point, const Vec3 &up);

	static Matrix4x4 *CreateFrustumMatrix(float left, float right, float bottom, float top, float near, float far);
	static Matrix4x4 *CreatePerspectiveMatrix(float fov, float aspect, float near, float far);

	static Matrix4x4 *CreateOrthoMatrix(float left, float right, float bottom, float top, float near, float far);

	//Creates and returns the reflection of in off of normal. Both Vectors should be normalized for proper results.
	static Vec3 *CreateReflectionVec3(const Vec3 &in, const Vec3 &normal);
	//Creates and returns the refraction of in through normal based on the indexOfRefraction. Both Vectors should be normalized for proper results.
	static Vec3 *CreateRefractionVec3(const Vec3 &in, const Vec3 &normal, float indexOfRefraction);

	static float Lerp(float a, float b, float t);
	static float QuadraticBezierLerp(float begin, float mid, float end, float t);
	static float CubicBezierLerp(float begin, float mid, float mid2, float end, float t);
	static float CubicBSpline(float cp[10], float t);

	static float Dot(const Vec3 &a, const Vec3 &b);
	static float Angle(const Vec3 &a, const Vec3 &b);
	static Vec3 Cross(const Vec3 &a, const Vec3 &b);
	static Vec3 *PCross(const Vec3 * const a, const Vec3 * const b);
	static float Length(const Vec3 &vec);
	static Vec3 *GetNormalizedVector(const Vec3 &vec);


	static Matrix3x3 *CreateSkewMatrix(const Vec3 & other);
};

