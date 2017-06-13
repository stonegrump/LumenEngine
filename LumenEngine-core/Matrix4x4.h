#pragma once

class Vec4;
class Matrix3x3;

class Matrix4x4
{
private:
	float *m_matrixArray;
public:


	Matrix4x4();
	Matrix4x4(const float * const values);
	Matrix4x4(const Vec4 &row1, const Vec4 &row2, const Vec4 &row3, const Vec4 &row4);
	Matrix4x4(float A00, float A10, float A20, float A30, float A01, float A11, float A21, float A31, float A02, float A12, float A22, float A32, float A03, float A13, float A23, float A33);
	Matrix4x4(const Matrix4x4 &other);
	Matrix4x4(const Matrix4x4 * const other);

	void Set(const float * const values);
	void Set(const Vec4 &row1, const Vec4 &row2, const Vec4 &row3, const Vec4 &row4);
	void Set(float A00, float A10, float A20, float A30, float A01, float A11, float A21, float A31, float A02, float A12, float A22, float A32, float A03, float A13, float A23, float A33);
	void Set(const Matrix4x4 &other);
	void Set(const Matrix4x4 * const other);

	float Trace();

	//Transposes the matrix and the returns the result
	static Matrix4x4 Identity();
	Matrix4x4 &Transpose();
	Matrix4x4 &Adjoint();
	bool Invert();
	float Det();
	float Det(int row, int col);


	Matrix4x4 &operator=(const Matrix4x4 &other);
	Matrix4x4 &operator=(const Matrix4x4 * const other);
	bool operator==(const Matrix4x4 &other);

	Matrix4x4 operator*(const Matrix4x4 &other);

	Matrix4x4 operator+(const Matrix4x4 &other);
	Matrix4x4 operator+(const Matrix3x3 &other);
	Matrix4x4 operator+(float value);
	Matrix4x4 operator-(const Matrix4x4 &other);
	Matrix4x4 operator-(const Matrix3x3 &other);
	Matrix4x4 operator-(float value);
	Matrix4x4 &operator-();
	Matrix4x4 operator/(float value);

	Matrix4x4 &operator*=(const Matrix4x4 &other);

	Matrix4x4 &operator+=(const Matrix4x4 &other);
	Matrix4x4 &operator+=(const Matrix3x3 &other);
	Matrix4x4 &operator+=(float value);
	Matrix4x4 &operator-=(const Matrix4x4 &other);
	Matrix4x4 &operator-=(const Matrix3x3 &other);
	Matrix4x4 &operator-=(float value);
	Matrix4x4 &operator/=(float value);
	float &operator()(int row, int col);
	float &operator[](int i);

	~Matrix4x4();
};

