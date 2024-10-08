#include "Vec2.h"
#include <math.h>
//definitions
Vec2::Vec2(){

}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin){

}

Vec2 Vec2::operator + (const Vec2 & rhs) const{
    return Vec2(x + rhs.x, y + rhs.y );
}

Vec2 Vec2::operator - (const Vec2 & rhs) const{
    return Vec2(x - rhs.x, y - rhs.y );
}

Vec2 Vec2::operator / (const float val) const{
    return Vec2(x/val,y/val);
}

Vec2 Vec2::operator * (const float val) const{
    return Vec2(x * val,y * val);
}

bool Vec2::operator == (const Vec2 & rhs) const{

    return (x == rhs.x && y == rhs.y);
}
bool Vec2::operator != (const Vec2 & rhs) const{

    return (x != rhs.x || y != rhs.y);
}
void Vec2::operator += (const Vec2 & rhs){

}
void Vec2::operator -= (const Vec2 & rhs){

}
void Vec2::operator *= (const float val){

}
void Vec2::operator /= (const float val){

}
float Vec2::dist(const Vec2 & rhs) const{
    
    return 0;
}
float Vec2::length()const{

    return 0;
}