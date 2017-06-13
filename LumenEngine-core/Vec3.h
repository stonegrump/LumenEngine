#pragma once

class Vec2;
class Vec4;
class Matrix3x3;

class Vec3
{
private:
	

public:

	float x, y, z;

	Vec3();
	Vec3(float x, float y, float z);
	Vec3(const Vec4 &other);
	Vec3(const Vec3 &other);
	Vec3(const Vec2 &other, float z);

	float Length() const;

	Vec3 &Normalize() { return (*this) / Length(); }

	float Dot(const Vec3 &other);

	float Angle(const Vec3 &other);

	Vec3 Cross(const Vec3 &other);
	Vec3 *PCross(const Vec3 * const other);

	Vec3 &operator=(const Vec3 &other);
	Vec3 &operator=(const Vec3 * const other);
	bool operator==(const Vec3 &other);

	Vec3 operator*(float value) const {
		return Vec3(x * value, y * value, z * value);
	}

	Vec3 operator+(const Vec3 &b) const {
		return Vec3(x + b.x, y + b.y, z + b.z);
	}
	Vec3 operator+(float value) const {
		return Vec3(x + value, y + value, z + value);
	}

	Vec3 operator-(const Vec3 &b) const {
		return Vec3(x - b.x, y - b.y, z - b.z);
	}
	Vec3 operator-(float value) const {
		return Vec3(x - value, y - value, z - value);
	}

	Vec3 operator/(float value) const {
		return Vec3(x / value, y / value, z / value);
	}
	Vec3 &operator-();

	Vec3 &operator+=(const Vec3 &other);
	Vec3 &operator+=(float value);
	Vec3 &operator-=(const Vec3 &other);
	Vec3 &operator-=(float value);
	Vec3 &operator/=(float value);
	Vec3 &operator*=(float value);

	~Vec3();
};

