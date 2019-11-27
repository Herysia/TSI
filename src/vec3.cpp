
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

float vec3::norm() const&
{
    return std::sqrt(x*x+y*y+z*z);
}

float vec3::dot(const vec3& v1)
{
    return x*v1.x+y*v1.y+z*v1.z;
}

vec3 vec3::cross(const vec3& v1)
{
    return vec3(y*v1.z-z*v1.y,
                z*v1.x-x*v1.z,
                x*v1.y-y*v1.x);
}

vec3 vec3::normalize() const&
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

vec3 vec3::operator+(const vec3& v1) const&
{
    vec3 temp=*this;
    temp+=v1;
    return temp;
}

vec3 vec3::operator-(const vec3& v1) const&
{
    vec3 temp=*this;
    temp-=v1;
    return temp;
}

vec3 vec3::operator*(float s) const&
{
    vec3 temp=*this;
    temp*=s;
    return temp;
}

vec3 vec3::operator/(float s) const&
{
    vec3 temp=*this;
    if(s != 0)
    {
        temp /= s;
    }
    else
    {
        temp.x = temp.y = temp.z = 0.0f;
    }
    return temp;
}
/*
vec3 vec3::operator*(const mat4& m)
{
    vec3 p = *this;
    vec3 r(m(0,0)*p.x+m(0,1)*p.y+m(0,2)*p.z+m(0,3),
           m(1,0)*p.x+m(1,1)*p.y+m(1,2)*p.z+m(1,3),
           m(2,0)*p.x+m(2,1)*p.y+m(2,2)*p.z+m(2,3));
    r=r/(m(3,0)*p.x+m(3,1)*p.y+m(3,2)*p.z+m(3,3));

    return r;
}*/
