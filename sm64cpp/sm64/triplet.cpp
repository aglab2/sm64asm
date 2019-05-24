#include <triplet.h>
#include <sm64.h>

float triplet::Length() const
{
    return sqrtf(x*x + y*y + z*z);
}

triplet triplet::Normal() const
{
    float length = Length();
    if (length == 0)
        return { 0, 0, 0 };

    return { x/length, y/length, z/length };
}

float triplet::Distance(const triplet& other) const
{
    return sqrtf(*this * other);
}

triplet& triplet::operator+=(const triplet& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

triplet& triplet::operator-=(const triplet& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

triplet& triplet::operator/=(const float divisor)
{
    x /= divisor;
    y /= divisor;
    z /= divisor;
    return *this;
}

triplet& triplet::operator*=(const float multiplier)
{
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    return *this;
}

float triplet::operator*(const triplet& other) const
{
    return x*other.x + y*other.y + z*other.z;
}

float triplet::operator^(const triplet& other) const
{
    return -1;
}