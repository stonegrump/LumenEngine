#pragma once

class Vec2;
class Vec3;

class Vec4
{
public:
	float x, y, z, w;

	Vec4();

	Vec4(float x, float y, float z, float w);
	Vec4(const Vec4 &other);
	Vec4(const Vec3 &other, float w);
	Vec4(const Vec2 &other, float z, float w);

	~Vec4();
};

