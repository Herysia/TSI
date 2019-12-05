
#include "vec2.hpp"
#include <cmath>
#include <cassert>
#include <iostream>

vec2::vec2()
    : x(0.0f), y(0.0f)
{
}

vec2::vec2(float x_param, float y_param)
    : x(x_param), y(y_param)
{
}

vec2 &vec2::operator+=(const vec2 &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

vec2 &vec2::operator-=(const vec2 &v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

vec2 &vec2::operator*=(float s)
{
    x *= s;
    y *= s;
    return *this;
}

vec2 &vec2::operator/=(float s)
{
    assert(fabs(s) > 10e-6);
    x /= s;
    y /= s;
    return *this;
}

std::ostream &operator<<(std::ostream &sout, const vec2 &vec)
{
    sout << vec.x << "," << vec.y;
    return sout;
}

float vec2::norm() const
{
    return std::sqrt(x * x + y * y);
}

float vec2::dot(const vec2 &v1)
{
    return x * v1.x + y * v1.y;
}

float vec2::cross(const vec2 &v1)
{
    return y * v1.x - x * v1.y;
}

vec2 vec2::normalize() const
{
    vec2 temp = *this;
    float len = this->norm();
    if (len != 0)
    {
        temp /= len;
    }
    else
    {
        temp.x = temp.y = 0.0f;
    }
    return temp;
}
vec2 operator+(const vec2 &v0, const vec2 &v1)
{
    vec2 temp = v0;
    temp += v1;
    return temp;
}

vec2 operator-(const vec2 &v0, const vec2 &v1)
{
    vec2 temp = v0;
    temp -= v1;
    return temp;
}

vec2 operator*(const vec2 &v0, float s)
{
    vec2 temp = v0;
    temp *= s;
    return temp;
}

vec2 operator*(float s, const vec2 &v0)
{
    return v0 * s;
}

vec2 operator/(const vec2 &v0, float s)
{
    vec2 temp = v0;
    temp /= s;
    return temp;
}
