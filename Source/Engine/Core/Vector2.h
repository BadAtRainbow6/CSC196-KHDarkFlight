#pragma once

namespace kiko
{

	class Vector2
	{
	public:
		float x, y;

	public:
		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float v) : x{ v }, y{ v } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ (float)x }, y{ (float)y } {}

		Vector2 Add(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
		Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

		Vector2 operator + (float s) const { return Vector2(x + s, y + s); }
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); }
		Vector2 operator * (float s) const { return Vector2(x * s, y * s); }
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		float LengthSqr() { return (x * x) + (y * y); }
		float Length() { return std::sqrt(LengthSqr()); }

		float DistanceSqr(const Vector2& v) const { return (v - *this).LengthSqr(); }
		float Distance(const Vector2& v) const { return (v - *this).Length(); }

		Vector2 Normalized() { return  *this / Length(); }
		void Normalize() { *this /= Length(); }

		float Angle() const { return std::atan2f(y, x); }
		Vector2 Rotate(float radians) const;

		static float SignedAngle(const Vector2& v1, const Vector2& v2);
		static float Angle(const Vector2& v1, const Vector2& v2);
		static float Dot(const Vector2& v1, const Vector2& v2);
	};

	inline Vector2 Vector2::Rotate(float radians) const
	{
		float _x = x * std::cos(radians) - y * std::sin(radians);
		float _y = x * std::sin(radians) + y * std::cos(radians);
		return { _x, _y };
	}

	// get the unsigned angle in radians between the normalized v1 and normalized v2
	inline float Vector2::Angle(const Vector2& v1, const Vector2& v2)
	{
		return std::acos(Dot(v1, v2));
	}

	// get the signed counterclockwise angle in radians between v1 and v2
	inline float Vector2::SignedAngle(const Vector2& v1, const Vector2& v2)
	{
		float y = v1.x * v2.y - v1.y * v2.x;
		float x = v1.x * v2.x + v1.y * v2.y;

		return std::atan2(y, x);
	}

	// get the dot product beteen v1 and v2 https://www.falstad.com/dotproduct/
	inline float Vector2::Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline std::istream& operator >> (std::istream& stream, Vector2& v)
	{
		std::string line;
		std::getline(stream, line);

		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find(",") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);

		return stream;
	}

	using vec2 = Vector2;
}