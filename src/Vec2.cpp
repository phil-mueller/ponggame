#include "Vec2.h"

Vec2::Vec2()
{
    x=0.0;
    y=0.0;
}

Vec2::Vec2(float xin, float yin)
{
    x=xin;
    y=yin;
}

Vec2 Vec2::operator+(Vec2 const& rhs)
{
    return Vec2(x+rhs.x,y+rhs.y);
}

Vec2& Vec2::operator+=(Vec2 const& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

Vec2 Vec2::operator*(float rhs)
{
    return Vec2(x*rhs,y*rhs);
}