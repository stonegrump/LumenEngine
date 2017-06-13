#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Vec4.h"


#pragma region Constructors
Matrix4x4::Matrix4x4()
{
	new float[16]{ 0 };
}

Matrix4x4::Matrix4x4(const float * const values)
{
	new float[16]{ 0 };
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = values[i];
}

Matrix4x4::Matrix4x4(const Vec4 &row1, const Vec4 &row2, const Vec4 &row3, const Vec4 &row4)
{
	m_matrixArray = new float[16]{ row1.x, row2.x, row3.x, row4.x, row1.y, row2.y, row3.y, row4.y, row1.z, row2.z, row3.z, row4.z, row1.w, row2.w, row3.w, row4.w };
}

Matrix4x4::Matrix4x4(float A00, float A10, float A20, float A30, float A01, float A11, float A21, float A31, float A02, float A12, float A22, float A32, float A03, float A13, float A23, float A33)
{
	m_matrixArray = new float[16]{ A00, A01, A02, A03, A10, A11, A12, A13, A20, A21, A22, A23, A30, A31, A32, A33 };
}

Matrix4x4::Matrix4x4(const Matrix4x4 &other)
{
	new float[16]{ 0 };
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = other.m_matrixArray[i];
}

Matrix4x4::Matrix4x4(const Matrix4x4 * const other)
{
	new float[16]{ 0 };
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = other->m_matrixArray[i];
}
#pragma endregion

#pragma region Set
void Matrix4x4::Set(const float * const values)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = values[i];
}

void Matrix4x4::Set(const Vec4 &row1, const Vec4 &row2, const Vec4 &row3, const Vec4 &row4)
{
	m_matrixArray = new float[16]{ row1.x, row2.x, row3.x, row4.x, row1.y, row2.y, row3.y, row4.y, row1.z, row2.z, row3.z, row4.z, row1.w, row2.w, row3.w, row4.w };
}

void Matrix4x4::Set(float A00, float A10, float A20, float A30, float A01, float A11, float A21, float A31, float A02, float A12, float A22, float A32, float A03, float A13, float A23, float A33)
{
	m_matrixArray = new float[16]{ A00, A01, A02, A03, A10, A11, A12, A13, A20, A21, A22, A23, A30, A31, A32, A33 };
}

void Matrix4x4::Set(const Matrix4x4 &other)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = other.m_matrixArray[i];
}

void Matrix4x4::Set(const Matrix4x4 * const other)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = other->m_matrixArray[i];
}
#pragma endregion

#pragma region Functions
float Matrix4x4::Trace()
{
	return m_matrixArray[0] + m_matrixArray[4] + m_matrixArray[8] + m_matrixArray[12];
}

Matrix4x4 Matrix4x4::Identity()
{
	return Matrix4x4(1, 0, 0, 0, 
						 0, 1, 0, 0, 
						 0, 0, 1, 0, 
						 0, 0, 0, 1);
}

Matrix4x4 & Matrix4x4::Transpose()
{
	float *temp = new float[16]{ 0 };

	for (int col = 0; col < 4; ++col)
		for (int row = 0; row < 4; ++row)
			temp[(col * 4) + row] = m_matrixArray[(row * 4) + col];

	delete[] m_matrixArray;
	m_matrixArray = temp;
	return *this;
}

Matrix4x4 & Matrix4x4::Adjoint()
{
	float *temp = new float[16]{ 0 };
	bool invert = false;
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			temp[(col * 4) + row] = (invert) ? Det(row, col) : -Det(row, col);
			invert = !invert;
		}
	}

	delete[] m_matrixArray;
	m_matrixArray = temp;
	this->Transpose();
	return *this;
}

bool Matrix4x4::Invert()
{
	float det = this->Det();
	if (det == 0)
		return false;

	Adjoint();
	(*this) /= det;
	return true;
}

float Matrix4x4::Det()
{
	return (m_matrixArray[0] * Det(0, 0)) - (m_matrixArray[4] * Det(0, 1)) + (m_matrixArray[8] * Det(0, 2)) - (m_matrixArray[12] * Det(0, 3));
}

float Matrix4x4::Det(int row, int col)
{
	float temp[9]{ 0 };
	int index = 0;
	for (int curCol = 0; curCol < 4; ++curCol) {
		if (curCol == col) continue;
		for (int curRow = 0; curRow < 4; ++curRow) {
			if (curRow == row) continue;
			temp[index++] = m_matrixArray[(curCol * 4) + curRow];
		}
	}
	return    (temp[0] * (temp[4] * temp[8] - temp[5] * temp[7]))
			- (temp[3] * (temp[1] * temp[8] - temp[2] * temp[7]))
			+ (temp[6] * (temp[1] * temp[5] - temp[2] * temp[4]));
}
#pragma endregion

#pragma region operators
Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & other)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = other.m_matrixArray[i];
	return *this;
}
Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 * const other)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = other->m_matrixArray[i];
	return *this;
}

bool Matrix4x4::operator==(const Matrix4x4 & other)
{
	for (int i = 0; i < 16; ++i)
		if (m_matrixArray[i] != other.m_matrixArray[i]) return false;
	return true;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & other)
{
	float *temp = new float[16]{ 0 };

	//Column 1
	temp[0] = (m_matrixArray[0] * other.m_matrixArray[0]) + (m_matrixArray[4] * other.m_matrixArray[1]) + (m_matrixArray[8] * other.m_matrixArray[2]) + (m_matrixArray[12] * other.m_matrixArray[3]);
	temp[1] = (m_matrixArray[1] * other.m_matrixArray[0]) + (m_matrixArray[5] * other.m_matrixArray[1]) + (m_matrixArray[9] * other.m_matrixArray[2]) + (m_matrixArray[13] * other.m_matrixArray[3]);
	temp[2] = (m_matrixArray[2] * other.m_matrixArray[0]) + (m_matrixArray[6] * other.m_matrixArray[1]) + (m_matrixArray[10] * other.m_matrixArray[2]) + (m_matrixArray[14] * other.m_matrixArray[3]);
	temp[3] = (m_matrixArray[3] * other.m_matrixArray[0]) + (m_matrixArray[7] * other.m_matrixArray[1]) + (m_matrixArray[11] * other.m_matrixArray[2]) + (m_matrixArray[15] * other.m_matrixArray[3]);

	//Column 2
	temp[4] = (m_matrixArray[0] * other.m_matrixArray[4]) + (m_matrixArray[4] * other.m_matrixArray[5]) + (m_matrixArray[8] * other.m_matrixArray[6]) + (m_matrixArray[12] * other.m_matrixArray[7]);
	temp[5] = (m_matrixArray[1] * other.m_matrixArray[4]) + (m_matrixArray[5] * other.m_matrixArray[5]) + (m_matrixArray[9] * other.m_matrixArray[6]) + (m_matrixArray[13] * other.m_matrixArray[7]);
	temp[6] = (m_matrixArray[2] * other.m_matrixArray[4]) + (m_matrixArray[6] * other.m_matrixArray[5]) + (m_matrixArray[10] * other.m_matrixArray[6]) + (m_matrixArray[14] * other.m_matrixArray[7]);
	temp[7] = (m_matrixArray[3] * other.m_matrixArray[4]) + (m_matrixArray[7] * other.m_matrixArray[5]) + (m_matrixArray[11] * other.m_matrixArray[6]) + (m_matrixArray[15] * other.m_matrixArray[7]);

	//Column 3
	temp[8] = (m_matrixArray[0] * other.m_matrixArray[8]) + (m_matrixArray[4] * other.m_matrixArray[9]) + (m_matrixArray[8] * other.m_matrixArray[10]) + (m_matrixArray[12] * other.m_matrixArray[11]);
	temp[9] = (m_matrixArray[1] * other.m_matrixArray[8]) + (m_matrixArray[5] * other.m_matrixArray[9]) + (m_matrixArray[9] * other.m_matrixArray[10]) + (m_matrixArray[13] * other.m_matrixArray[11]);
	temp[10] = (m_matrixArray[2] * other.m_matrixArray[8]) + (m_matrixArray[6] * other.m_matrixArray[9]) + (m_matrixArray[10] * other.m_matrixArray[10]) + (m_matrixArray[14] * other.m_matrixArray[11]);
	temp[11] = (m_matrixArray[3] * other.m_matrixArray[8]) + (m_matrixArray[7] * other.m_matrixArray[9]) + (m_matrixArray[11] * other.m_matrixArray[10]) + (m_matrixArray[15] * other.m_matrixArray[11]);

	//Column 4
	temp[12] = (m_matrixArray[0] * other.m_matrixArray[12]) + (m_matrixArray[4] * other.m_matrixArray[13]) + (m_matrixArray[8] * other.m_matrixArray[14]) + (m_matrixArray[12] * other.m_matrixArray[15]);
	temp[13] = (m_matrixArray[1] * other.m_matrixArray[12]) + (m_matrixArray[5] * other.m_matrixArray[13]) + (m_matrixArray[9] * other.m_matrixArray[14]) + (m_matrixArray[13] * other.m_matrixArray[15]);
	temp[14] = (m_matrixArray[2] * other.m_matrixArray[12]) + (m_matrixArray[6] * other.m_matrixArray[13]) + (m_matrixArray[10] * other.m_matrixArray[14]) + (m_matrixArray[14] * other.m_matrixArray[15]);
	temp[15] = (m_matrixArray[3] * other.m_matrixArray[12]) + (m_matrixArray[7] * other.m_matrixArray[13]) + (m_matrixArray[11] * other.m_matrixArray[14]) + (m_matrixArray[15] * other.m_matrixArray[15]);

	Matrix4x4 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix4x4 & Matrix4x4::operator*=(const Matrix4x4 & other)
{
	float *temp = new float[16]{ 0 };

	//Column 1
	temp[0] = (m_matrixArray[0] * other.m_matrixArray[0]) + (m_matrixArray[4] * other.m_matrixArray[1]) + (m_matrixArray[8] * other.m_matrixArray[2]) + (m_matrixArray[12] * other.m_matrixArray[3]);
	temp[1] = (m_matrixArray[1] * other.m_matrixArray[0]) + (m_matrixArray[5] * other.m_matrixArray[1]) + (m_matrixArray[9] * other.m_matrixArray[2]) + (m_matrixArray[13] * other.m_matrixArray[3]);
	temp[2] = (m_matrixArray[2] * other.m_matrixArray[0]) + (m_matrixArray[6] * other.m_matrixArray[1]) + (m_matrixArray[10] * other.m_matrixArray[2]) + (m_matrixArray[14] * other.m_matrixArray[3]);
	temp[3] = (m_matrixArray[3] * other.m_matrixArray[0]) + (m_matrixArray[7] * other.m_matrixArray[1]) + (m_matrixArray[11] * other.m_matrixArray[2]) + (m_matrixArray[15] * other.m_matrixArray[3]);

	//Column 2
	temp[4] = (m_matrixArray[0] * other.m_matrixArray[4]) + (m_matrixArray[4] * other.m_matrixArray[5]) + (m_matrixArray[8] * other.m_matrixArray[6]) + (m_matrixArray[12] * other.m_matrixArray[7]);
	temp[5] = (m_matrixArray[1] * other.m_matrixArray[4]) + (m_matrixArray[5] * other.m_matrixArray[5]) + (m_matrixArray[9] * other.m_matrixArray[6]) + (m_matrixArray[13] * other.m_matrixArray[7]);
	temp[6] = (m_matrixArray[2] * other.m_matrixArray[4]) + (m_matrixArray[6] * other.m_matrixArray[5]) + (m_matrixArray[10] * other.m_matrixArray[6]) + (m_matrixArray[14] * other.m_matrixArray[7]);
	temp[7] = (m_matrixArray[3] * other.m_matrixArray[4]) + (m_matrixArray[7] * other.m_matrixArray[5]) + (m_matrixArray[11] * other.m_matrixArray[6]) + (m_matrixArray[15] * other.m_matrixArray[7]);

	//Column 3
	temp[8] = (m_matrixArray[0] * other.m_matrixArray[8]) + (m_matrixArray[4] * other.m_matrixArray[9]) + (m_matrixArray[8] * other.m_matrixArray[10]) + (m_matrixArray[12] * other.m_matrixArray[11]);
	temp[9] = (m_matrixArray[1] * other.m_matrixArray[8]) + (m_matrixArray[5] * other.m_matrixArray[9]) + (m_matrixArray[9] * other.m_matrixArray[10]) + (m_matrixArray[13] * other.m_matrixArray[11]);
	temp[10] = (m_matrixArray[2] * other.m_matrixArray[8]) + (m_matrixArray[6] * other.m_matrixArray[9]) + (m_matrixArray[10] * other.m_matrixArray[10]) + (m_matrixArray[14] * other.m_matrixArray[11]);
	temp[11] = (m_matrixArray[3] * other.m_matrixArray[8]) + (m_matrixArray[7] * other.m_matrixArray[9]) + (m_matrixArray[11] * other.m_matrixArray[10]) + (m_matrixArray[15] * other.m_matrixArray[11]);

	//Column 4
	temp[12] = (m_matrixArray[0] * other.m_matrixArray[12]) + (m_matrixArray[4] * other.m_matrixArray[13]) + (m_matrixArray[8] * other.m_matrixArray[14]) + (m_matrixArray[12] * other.m_matrixArray[15]);
	temp[13] = (m_matrixArray[1] * other.m_matrixArray[12]) + (m_matrixArray[5] * other.m_matrixArray[13]) + (m_matrixArray[9] * other.m_matrixArray[14]) + (m_matrixArray[13] * other.m_matrixArray[15]);
	temp[14] = (m_matrixArray[2] * other.m_matrixArray[12]) + (m_matrixArray[6] * other.m_matrixArray[13]) + (m_matrixArray[10] * other.m_matrixArray[14]) + (m_matrixArray[14] * other.m_matrixArray[15]);
	temp[15] = (m_matrixArray[3] * other.m_matrixArray[12]) + (m_matrixArray[7] * other.m_matrixArray[13]) + (m_matrixArray[11] * other.m_matrixArray[14]) + (m_matrixArray[15] * other.m_matrixArray[15]);

	delete[] m_matrixArray;
	m_matrixArray = temp;

	return *this;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 & other)
{
	float *temp = new float[16]{ 0 };
	for (int i = 0; i < 16; ++i)
		temp[i] = m_matrixArray[i] + other.m_matrixArray[i];

	Matrix4x4 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix4x4 Matrix4x4::operator+(const Matrix3x3 & other)
{
	return Matrix4x4(m_matrixArray[0] + other[0], m_matrixArray[1] + other[1], m_matrixArray[2] + other[2], m_matrixArray[3],
		m_matrixArray[4] + other[3], m_matrixArray[5] + other[4], m_matrixArray[6] + other[5], m_matrixArray[7],
		m_matrixArray[8] + other[6], m_matrixArray[9] + other[7], m_matrixArray[10] + other[8], m_matrixArray[11],
		m_matrixArray[12], m_matrixArray[13], m_matrixArray[14], m_matrixArray[15]);
}
Matrix4x4 & Matrix4x4::operator+=(const Matrix4x4 & other)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] += other.m_matrixArray[i];

	return *this;
}

Matrix4x4 & Matrix4x4::operator+=(const Matrix3x3 & other)
{
	m_matrixArray[0] += other[0];
	m_matrixArray[1] += other[1];
	m_matrixArray[2] += other[2];
	m_matrixArray[4] += other[3]; 
	m_matrixArray[5] += other[4]; 
	m_matrixArray[6] += other[5];
	m_matrixArray[8] += other[6]; 
	m_matrixArray[9] += other[7]; 
	m_matrixArray[10] += other[8];
	return *this;
}

Matrix4x4 Matrix4x4::operator+(float value)
{
	float *temp = new float[16]{ 0 };
	for (int i = 0; i < 16; ++i)
		temp[i] = m_matrixArray[i] + value;

	Matrix4x4 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix4x4 & Matrix4x4::operator+=(float value)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] += value;

	return *this;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 & other)
{
	float *temp = new float[16]{ 0 };
	for (int i = 0; i < 16; ++i)
		temp[i] = m_matrixArray[i] - other.m_matrixArray[i];

	Matrix4x4 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix4x4 Matrix4x4::operator-(const Matrix3x3 & other)
{
	return Matrix4x4(m_matrixArray[0] - other[0], m_matrixArray[1] - other[1], m_matrixArray[2] - other[2], m_matrixArray[3],
		m_matrixArray[4] - other[3], m_matrixArray[5] - other[4], m_matrixArray[6] - other[5], m_matrixArray[7],
		m_matrixArray[8] - other[6], m_matrixArray[9] - other[7], m_matrixArray[10] - other[8], m_matrixArray[11],
		m_matrixArray[12], m_matrixArray[13], m_matrixArray[14], m_matrixArray[15]);
}
Matrix4x4 & Matrix4x4::operator-=(const Matrix4x4 & other)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] -= other.m_matrixArray[i];

	return *this;
}

Matrix4x4 & Matrix4x4::operator-=(const Matrix3x3 & other)
{
	m_matrixArray[0] -= other[0];
	m_matrixArray[1] -= other[1];
	m_matrixArray[2] -= other[2];
	m_matrixArray[4] -= other[3];
	m_matrixArray[5] -= other[4];
	m_matrixArray[6] -= other[5];
	m_matrixArray[8] -= other[6];
	m_matrixArray[9] -= other[7];
	m_matrixArray[10] -= other[8];
	return *this;
}

Matrix4x4 Matrix4x4::operator-(float value)
{
	float *temp = new float[16]{ 0 };
	for (int i = 0; i < 16; ++i)
		temp[i] = m_matrixArray[i] - value;

	Matrix4x4 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix4x4 & Matrix4x4::operator-()
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] = -m_matrixArray[i];
	return *this;
}
Matrix4x4 & Matrix4x4::operator-=(float value)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] -= value;

	return *this;
}

Matrix4x4 Matrix4x4::operator/(float value)
{
	float *temp = new float[16]{ 0 };
	for (int i = 0; i < 16; ++i)
		temp[i] = m_matrixArray[i] / value;

	Matrix4x4 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix4x4 & Matrix4x4::operator/=(float value)
{
	for (int i = 0; i < 16; ++i)
		m_matrixArray[i] /= value;

	return *this;
}

float & Matrix4x4::operator()(int row, int col)
{
	return m_matrixArray[(col * 4) + row];
}

float & Matrix4x4::operator[](int i)
{
	return m_matrixArray[i];
}
#pragma endregion

Matrix4x4::~Matrix4x4()
{
	delete[] m_matrixArray;
	m_matrixArray = 0;
}
