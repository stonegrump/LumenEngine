#pragma once

class Vec3;

class Matrix3x3
{
private:
	float *m_matrixArray;
public:
	

	Matrix3x3();
	Matrix3x3(const float * const values);
	Matrix3x3(const Vec3 &row1, const Vec3 &row2, const Vec3 &row3);
	Matrix3x3(float A00, float A10, float A20, float A01, float A11, float A21, float A02, float A12, float A22);
	Matrix3x3(const Matrix3x3 &other);
	Matrix3x3(const Matrix3x3 * const other);

	void Set(const float * const values);
	void Set(const Vec3 &row1, const Vec3 &row2, const Vec3 &row3);
	void Set(float A00, float A10, float A20, float A01, float A11, float A21, float A02, float A12, float A22);
	void Set(const Matrix3x3 &other);
	void Set(const Matrix3x3 * const other);

	float Trace();
	
	static Matrix3x3 Identity();
	//Transposes the matrix and the returns the result
	Matrix3x3 &Transpose();
	Matrix3x3 &Adjoint();
	bool Invert();
	float Det();
	float Det(int row, int col);


	Matrix3x3 &operator=(const Matrix3x3 &other);
	Matrix3x3 &operator=(const Matrix3x3 * const other);
	bool operator==(const Matrix3x3 &other);

	Matrix3x3 operator*(const Matrix3x3 &other);
	Matrix3x3 operator*(float f);

	Matrix3x3 operator+(const Matrix3x3 &other);
	Matrix3x3 operator+(float value);
	Matrix3x3 operator-(const Matrix3x3 &other);
	Matrix3x3 operator-(float value);
	Matrix3x3 &operator-();
	Matrix3x3 operator/(float value);

	Matrix3x3 &operator*=(const Matrix3x3 &other);
	Matrix3x3 &operator*=(float f);

	Matrix3x3 &operator+=(const Matrix3x3 &other);
	Matrix3x3 &operator+=(float value);
	Matrix3x3 &operator-=(const Matrix3x3 &other);
	Matrix3x3 &operator-=(float value);
	Matrix3x3 &operator/=(float value);
	float &operator()(int row, int col);
	float &operator()(int row, int col) const;
	float &operator[](int i);
	float &operator[](int i) const;

	~Matrix3x3();
};

