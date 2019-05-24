#pragma once

struct triplet
{
	float x;
	float y;
	float z;

	float Length() const;
	triplet Normal() const;
	float Distance(const triplet& other) const;

	triplet& operator+=(const triplet& other);
	triplet& operator-=(const triplet& other);
	triplet& operator/=(const float divisor);
	triplet& operator*=(const float multiplier);
	
	triplet operator+(const triplet& other) { return *this += other; }
	triplet operator-(const triplet& other) { return *this -= other; }
	triplet operator/(const float divisor) { return *this /= divisor; }
	triplet operator*(const float multiplier) { return *this *= multiplier; }

	float operator*(const triplet& other) const;
	float operator^(const triplet& other) const;
};

template<typename T>
class ttriplet
{
public:
	ttriplet(T x, T y, T z) : x(x), y(y), z(z) { }

	union
	{
		struct
		{
			T x;
			T y;
			T z;
		};
		T val[3];
	};
};