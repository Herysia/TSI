
#include "vec3.hpp"
#include <cmath>
#include <cassert>
#include <iostream>

vec3::vec3()
    : x(0.0f), y(0.0f), z(0.0f)
{
}

vec3::vec3(float x_param, float y_param, float z_param)
    : x(x_param), y(y_param), z(z_param)
{
}

vec3 &vec3::operator+=(const vec3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3 &vec3::operator-=(const vec3 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec3 &vec3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

vec3 &vec3::operator/=(float s)
{
    if (s != 0)
    {
        x /= s;
        y /= s;
        z /= s;
    }
    else
    {
        x = y = z = 0.0f;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &sout, const vec3 &vec)
{
    sout << vec.x << "," << vec.y << "," << vec.z;
    return sout;
}

float vec3::norm() const
{
    return std::sqrt(x * x + y * y + z * z);
}

float vec3::dot(const vec3 &v1) const
{
    return x * v1.x + y * v1.y + z * v1.z;
}

vec3 vec3::cross(const vec3 &v1) const
{
    return vec3(y * v1.z - z * v1.y,
                z * v1.x - x * v1.z,
                x * v1.y - y * v1.x);
}

vec3 vec3::normalize() const
{
    vec3 temp = *this;
    float len = this->norm();
    if (len != 0)
    {
        temp /= len;
    }
    else
    {
        temp.x = temp.y = temp.z = 0.0f;
    }
    return temp;
}
vec3 vec3::clamp() const
{
    vec3 temp = *this;
    while (temp.y > M_PI)
        temp.y -= 2 * M_PI;
    while (temp.y < -M_PI)
        temp.y += 2 * M_PI;
    float xmax = 89.0f * M_PI / 180.0f;
    if (temp.x > xmax)
        temp.x = xmax;
    if (temp.x < -xmax)
        temp.x = -xmax;
    temp.z = 0.0f;
    return temp;
}
vec3 operator+(const vec3 &v0, const vec3 &v1)
{
    vec3 temp = v0;
    temp += v1;
    return temp;
}

vec3 operator-(const vec3 &v0, const vec3 &v1)
{
    vec3 temp = v0;
    temp -= v1;
    return temp;
}

vec3 operator*(const vec3 &v0, float s)
{
    vec3 temp = v0;
    temp *= s;
    return temp;
}

vec3 operator/(const vec3 &v0, float s)
{
    vec3 temp = v0;
    temp /= s;
    return temp;
}
