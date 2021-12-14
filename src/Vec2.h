// Vector help class
#ifndef VEC2_H
#define VEC2_H

class Vec2
{
    public:
        Vec2();
        Vec2(float xin, float yin);
        Vec2 operator+(Vec2 const& rhs);
        Vec2& operator+=(Vec2 const& rhs);
        Vec2 operator*(float rhs);
        float x, y;
};

#endif