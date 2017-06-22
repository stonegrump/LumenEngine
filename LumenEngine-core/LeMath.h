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

	static Matrix4x4 *CreateScaleMatrixP(float x, float y, float z);
	static Matrix4x4 *CreateScaleMatrixP(const Vec3 &v);
	static Matrix4x4 *CreateScaleMatrixP(float a);
	static Matrix4x4 *CreateRotationMatrixP(EAxis axis, float angle);
	static Matrix4x4 *CreateRotationMatrixP(float x, float y, float z);
	static Matrix4x4 *CreateRotationMatrixP(float angle, const Vec3 &base);
	static Matrix4x4 *CreateTranslationMatrixP(float x, float y, float z);
	static Matrix4x4 *CreateTranslationMatrixP(const Vec3 &v);

	static Matrix4x4 CreateScaleMatrix(float x, float y, float z);
	static Matrix4x4 CreateScaleMatrix(const Vec3 &v);
	static Matrix4x4 CreateScaleMatrix(float a);
	static Matrix4x4 CreateRotationMatrix(EAxis axis, float angle);
	static Matrix4x4 CreateRotationMatrix(float x, float y, float z);
	static Matrix4x4 CreateRotationMatrix(float angle, const Vec3 &base);
	static Matrix4x4 CreateTranslationMatrix(float x, float y, float z);
	static Matrix4x4 CreateTranslationMatrix(const Vec3 &v);

	static void CreateScaleMatrix(float x, float y, float z, Matrix4x4 *outMat);
	static void CreateScaleMatrix(const Vec3 &v, Matrix4x4 *outMat);
	static void CreateScaleMatrix(float a, Matrix4x4 *outMat);
	static void CreateRotationMatrix(EAxis axis, float angle, Matrix4x4 *outMat);
	static void CreateRotationMatrix(float x, float y, float z, Matrix4x4 *outMat);
	static void CreateRotationMatrix(float angle, const Vec3 &base, Matrix4x4 *outMat);
	static void CreateTranslationMatrix(float x, float y, float z, Matrix4x4 *outMat);
	static void CreateTranslationMatrix(const Vec3 &v, Matrix4x4 *outMat);

	static Matrix4x4 *CreateLookAtMatrix(const Vec3 &eye, const Vec3 &point, const Vec3 &up);

	static Matrix4x4 *CreateFrustumMatrix(float left, float right, float bottom, float top, float _near, float _far);
	static Matrix4x4 *CreatePerspectiveMatrix(float fov, float aspect, float _near, float _far);

	static Matrix4x4 *CreateOrthoMatrix(float left, float right, float bottom, float top, float _near, float _far);

	static void CreateLookAtMatrix(const Vec3 &eye, const Vec3 &point, const Vec3 &up, Matrix4x4 *outMat);
		    
	static void CreateFrustumMatrix(float left, float right, float bottom, float top, float _near, float _far, Matrix4x4 *outMat);
	static void CreatePerspectiveMatrix(float fov, float aspect, float _near, float _far, Matrix4x4 *outMat);
		    
	static void CreateOrthoMatrix(float left, float right, float bottom, float top, float _near, float _far, Matrix4x4 *outMat);

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

