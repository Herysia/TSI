
#include "vec3.hpp"
#include <cmath>
#include <cassert>
#include <iostream>


vec3::vec3()
    :x(0.0f),y(0.0f),z(0.0f)
{}

vec3::vec3(float x_param,float y_param,float z_param)
    :x(x_param),y(y_param),z(z_param)
{}

vec3& vec3::operator+=(const vec3& v)
{
    x+=v.x;
    y+=v.y;
    z+=v.z;
    return *this;
}

vec3& vec3::operator-=(const vec3& v)
{
    x-=v.x;
    y-=v.y;
    z-=v.z;
    return *this;
}

vec3& vec3::operator*=(float s)
{
    x*=s; y*=s; z*=s;
    return *this;
}

vec3& vec3::operator/=(float s)
{
    assert(fabs(s)>10e-6);
    x/=s; y/=s; z/=s;
    return *this;
}

std::ostream& vec3::operator<<(std::ostream& sout)
{
    sout<< x <<","<< y <<","<< z;
    return sout;
}

float vec3::norm() const
{
    return std::sqrt(x*x+y*y+z*z);
}

float vec3::dot(const vec3& v1) const
{
    return x*v1.x+y*v1.y+z*v1.z;
}

vec3 vec3::cross(const vec3& v1) const
{
    return vec3(y*v1.z-z*v1.y,
                z*v1.x-x*v1.z,
                x*v1.y-y*v1.x);
}

vec3 vec3::normalize() const
{
    vec3 temp = *this;
    float len = this->norm();
    if(len != 0)
    {
        temp /= len;
    }
    else
    {
        temp.x = temp.y = temp.z = 0.0f;
    }
    return temp;
}

vec3 operator+(const vec3& v0,const vec3& v1)
{
    vec3 temp=v0;
    temp+=v1;
    return temp;
}

vec3 operator-(const vec3& v0,const vec3& v1)
{
    vec3 temp=v0;
    temp-=v1;
    return temp;
}

vec3 operator*(const vec3& v0,float s)
{
    vec3 temp=v0;
    temp*=s;
    return temp;
}


vec3 operator/(const vec3& v0,float s)
{
    vec3 temp=v0;temp/=s;return temp;
}


