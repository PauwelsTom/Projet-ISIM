#pragma once 
#include "raymarcher.hh"

class Ray {
public:
    Point3 origin_;
    Vector3 direction_;

    Ray() {}

    Ray(const Point3& origin, const Vector3& direction) : origin_(origin), direction_(direction) {}
    
    Point3 at(double t) const {
        return origin_ + direction_*t;
    }
    
};