#pragma once

#include "raymarcher.hh"


class Camera {
public:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vector3 horizontal;
    Vector3 vertical;

    Camera() {
        origin = Point3(0, 0, 0);
        double aspect_ratio = 16.0 / 9.0;
        double viewport_height = 2.0;
        double viewport_width = aspect_ratio * viewport_height;
        double focal_length = 1.25;

        horizontal = Vector3(viewport_width, 0.0, 0.0);
        vertical = Vector3(0.0, viewport_height, 0.0);
        lowerLeftCorner = origin - horizontal/2 - vertical/2 - Vector3(0, 0, focal_length);
    }

    Ray getRay(double u, double v) const {
        return Ray(origin, lowerLeftCorner + horizontal * u + vertical * v - origin);
    }
};
