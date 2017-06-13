#include "Matrix3x3.h"
#include "Vec3.h"

#pragma region Constructors
Matrix3x3::Matrix3x3()
{
	m_matrixArray = new float[9]{ 0 };
}

Matrix3x3::Matrix3x3(const float * const values)
{
	m_matrixArray = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = values[i];
}

Matrix3x3::Matrix3x3(const Vec3 & row1, const Vec3 & row2, const Vec3 & row3)
{
	m_matrixArray = new float[9]{ row1.x, row2.x, row3.x, row1.y, row2.y, row3.y, row1.z, row2.z, row3.z };
}

Matrix3x3::Matrix3x3(float A00, float A10, float A20, float A01, float A11, float A21, float A02, float A12, float A22)
{
	m_matrixArray = new float[9]{ A00, A01, A02, A10, A11, A12, A20, A21, A22 };
}

Matrix3x3::Matrix3x3(const Matrix3x3 &other)
{
	m_matrixArray = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = other.m_matrixArray[i];
}

Matrix3x3::Matrix3x3(const Matrix3x3 * const other)
{
	m_matrixArray = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = other->m_matrixArray[i];
}
#pragma endregion

#pragma region Set
void Matrix3x3::Set(const float * const values)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = values[i];
}

void Matrix3x3::Set(const Vec3 & row1, const Vec3 & row2, const Vec3 & row3)
{
	m_matrixArray = new float[9]{ row1.x, row2.x, row3.x, row1.y, row2.y, row3.y, row1.z, row2.z, row3.z };
}

void Matrix3x3::Set(float A00, float A10, float A20, float A01, float A11, float A21, float A02, float A12, float A22)
{
	m_matrixArray = new float[9]{ A00, A01, A02, A10, A11, A12, A20, A21, A22 };
}

void Matrix3x3::Set(const Matrix3x3 &other)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = other.m_matrixArray[i];
}

void Matrix3x3::Set(const Matrix3x3 * const other)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = other->m_matrixArray[i];
}
#pragma endregion

#pragma region Functions
float Matrix3x3::Trace()
{
	return m_matrixArray[0] + m_matrixArray[4] + m_matrixArray[8];
}

Matrix3x3 Matrix3x3::Identity()
{
	return Matrix3x3(1, 0, 0,
						 0, 1, 0,
						 0, 0, 1);
}

Matrix3x3 & Matrix3x3::Transpose()
{
	float *temp = new float[9]{ 0 };
	
	for (int col = 0; col < 3; ++col)
		for (int row = 0; row < 3; ++row)
			temp[(col * 3) + row] = m_matrixArray[(row * 3) + col];

	delete[] m_matrixArray;
	m_matrixArray = temp;
	return *this;
}

Matrix3x3 & Matrix3x3::Adjoint()
{
	float *temp = new float[9]{ 0 };
	bool invert = false;
	for (int col = 0; col < 3; ++col) {
		for (int row = 0; row < 3; ++row) {
			temp[(col * 3) + row] = (invert) ? Det(row, col) : -Det(row, col);
			invert = !invert;
		}
	}
	delete[] m_matrixArray;
	m_matrixArray = temp;
	this->Transpose();
	return *this;
}

bool Matrix3x3::Invert()
{
	float det = this->Det();
	if (det == 0)
		return false;

	Adjoint();
	(*this) /= det;
	//delete temp;
	return true;
}

float Matrix3x3::Det()
{
	return    (m_matrixArray[0] * (m_matrixArray[4] * m_matrixArray[8] - m_matrixArray[5] * m_matrixArray[7])) 
			- (m_matrixArray[3] * (m_matrixArray[1] * m_matrixArray[8] - m_matrixArray[2] * m_matrixArray[7])) 
			+ (m_matrixArray[6] * (m_matrixArray[1] * m_matrixArray[5] - m_matrixArray[2] * m_matrixArray[4]));
}

float Matrix3x3::Det(int row, int col)
{
	float temp[4]{ 0 };
	int index = 0;
	for (int curCol = 0; curCol < 3; ++curCol) {
		if (curCol == col) continue;
		for (int curRow = 0; curRow < 3; ++curRow) {
			if (curRow == row) continue;
			temp[index++] = m_matrixArray[(curCol * 3) + curRow];
		}
	}
	return temp[0] * temp[3] - temp[1] * temp[2];
}
#pragma endregion

#pragma region operators
Matrix3x3 & Matrix3x3::operator=(const Matrix3x3 & other)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = other.m_matrixArray[i];
	return *this;
}
Matrix3x3 & Matrix3x3::operator=(const Matrix3x3 * const other)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = other->m_matrixArray[i];
	return *this;
}

bool Matrix3x3::operator==(const Matrix3x3 & other)
{
	for (int i = 0; i < 9; ++i)
		if (m_matrixArray[i] != other.m_matrixArray[i]) return false;
	return true;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3 & other)
{
	float *temp = new float[9]{ 0 };

	//Column 1
	temp[0] = (m_matrixArray[0] * other.m_matrixArray[0]) + (m_matrixArray[3] * other.m_matrixArray[1]) + (m_matrixArray[6] * other.m_matrixArray[2]);
	temp[1] = (m_matrixArray[1] * other.m_matrixArray[0]) + (m_matrixArray[4] * other.m_matrixArray[1]) + (m_matrixArray[7] * other.m_matrixArray[2]);
	temp[2] = (m_matrixArray[2] * other.m_matrixArray[0]) + (m_matrixArray[5] * other.m_matrixArray[1]) + (m_matrixArray[8] * other.m_matrixArray[2]);

	//Column 2
	temp[3] = (m_matrixArray[0] * other.m_matrixArray[3]) + (m_matrixArray[3] * other.m_matrixArray[4]) + (m_matrixArray[6] * other.m_matrixArray[5]);
	temp[4] = (m_matrixArray[1] * other.m_matrixArray[3]) + (m_matrixArray[4] * other.m_matrixArray[4]) + (m_matrixArray[7] * other.m_matrixArray[5]);
	temp[5] = (m_matrixArray[2] * other.m_matrixArray[3]) + (m_matrixArray[5] * other.m_matrixArray[4]) + (m_matrixArray[8] * other.m_matrixArray[5]);
	
	//Column 3
	temp[6] = (m_matrixArray[0] * other.m_matrixArray[6]) + (m_matrixArray[3] * other.m_matrixArray[7]) + (m_matrixArray[6] * other.m_matrixArray[7]);
	temp[7] = (m_matrixArray[1] * other.m_matrixArray[6]) + (m_matrixArray[4] * other.m_matrixArray[7]) + (m_matrixArray[7] * other.m_matrixArray[7]);
	temp[8] = (m_matrixArray[2] * other.m_matrixArray[6]) + (m_matrixArray[5] * other.m_matrixArray[7]) + (m_matrixArray[8] * other.m_matrixArray[7]);

	Matrix3x3 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix3x3 Matrix3x3::operator*(float f)
{
	float *temp = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		temp[i] = m_matrixArray[i] * f;

	Matrix3x3 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix3x3 & Matrix3x3::operator*=(const Matrix3x3 & other)
{
	float *temp = new float[9]{ 0 };

	//Column 1
	temp[0] = (m_matrixArray[0] * other.m_matrixArray[0]) + (m_matrixArray[3] * other.m_matrixArray[1]) + (m_matrixArray[6] * other.m_matrixArray[2]);
	temp[1] = (m_matrixArray[1] * other.m_matrixArray[0]) + (m_matrixArray[4] * other.m_matrixArray[1]) + (m_matrixArray[7] * other.m_matrixArray[2]);
	temp[2] = (m_matrixArray[2] * other.m_matrixArray[0]) + (m_matrixArray[5] * other.m_matrixArray[1]) + (m_matrixArray[8] * other.m_matrixArray[2]);

	//Column 2
	temp[3] = (m_matrixArray[0] * other.m_matrixArray[3]) + (m_matrixArray[3] * other.m_matrixArray[4]) + (m_matrixArray[6] * other.m_matrixArray[5]);
	temp[4] = (m_matrixArray[1] * other.m_matrixArray[3]) + (m_matrixArray[4] * other.m_matrixArray[4]) + (m_matrixArray[7] * other.m_matrixArray[5]);
	temp[5] = (m_matrixArray[2] * other.m_matrixArray[3]) + (m_matrixArray[5] * other.m_matrixArray[4]) + (m_matrixArray[8] * other.m_matrixArray[5]);

	//Column 3
	temp[6] = (m_matrixArray[0] * other.m_matrixArray[6]) + (m_matrixArray[3] * other.m_matrixArray[7]) + (m_matrixArray[6] * other.m_matrixArray[7]);
	temp[7] = (m_matrixArray[1] * other.m_matrixArray[6]) + (m_matrixArray[4] * other.m_matrixArray[7]) + (m_matrixArray[7] * other.m_matrixArray[7]);
	temp[8] = (m_matrixArray[2] * other.m_matrixArray[6]) + (m_matrixArray[5] * other.m_matrixArray[7]) + (m_matrixArray[8] * other.m_matrixArray[7]);

	delete[] m_matrixArray;
	m_matrixArray = temp;

	return *this;
}

Matrix3x3 & Matrix3x3::operator*=(float f)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] *= f;

	return *this;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3 & other)
{
	float *temp = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		temp[i] = m_matrixArray[i] + other.m_matrixArray[i];

	Matrix3x3 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix3x3 & Matrix3x3::operator+=(const Matrix3x3 & other)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] += other.m_matrixArray[i];

	return *this;
}

Matrix3x3 Matrix3x3::operator+(float value)
{
	float *temp = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		temp[i] = m_matrixArray[i] + value;

	Matrix3x3 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix3x3 & Matrix3x3::operator+=(float value)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] += value;

	return *this;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3 & other)
{
	float *temp = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		temp[i] = m_matrixArray[i] - other.m_matrixArray[i];

	Matrix3x3 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix3x3 & Matrix3x3::operator-=(const Matrix3x3 & other)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] -= other.m_matrixArray[i];

	return *this;
}

Matrix3x3 Matrix3x3::operator-(float value)
{
	float *temp = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		temp[i] = m_matrixArray[i] - value;

	Matrix3x3 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix3x3 &Matrix3x3::operator-()
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] = -m_matrixArray[i];
	return *this;
}
Matrix3x3 & Matrix3x3::operator-=(float value)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] -= value;

	return *this;
}

Matrix3x3 Matrix3x3::operator/(float value)
{
	float *temp = new float[9]{ 0 };
	for (int i = 0; i < 9; ++i)
		temp[i] = m_matrixArray[i] / value;

	Matrix3x3 returnMat(temp);
	delete[] temp;
	return returnMat;
}
Matrix3x3 & Matrix3x3::operator/=(float value)
{
	for (int i = 0; i < 9; ++i)
		m_matrixArray[i] /= value;

	return *this;
}

float & Matrix3x3::operator()(int row, int col)
{
	return m_matrixArray[(col * 3) + row];
}

float & Matrix3x3::operator()(int row, int col) const
{
	return m_matrixArray[(col * 3) + row];
}

float & Matrix3x3::operator[](int i)
{
	return m_matrixArray[i];
}
float & Matrix3x3::operator[](int i) const
{
	return m_matrixArray[i];
}
#pragma endregion

Matrix3x3::~Matrix3x3()
{
	delete[] m_matrixArray;
	m_matrixArray = 0;
}
