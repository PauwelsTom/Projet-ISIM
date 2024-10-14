#pragma once

#include "raymarcher.hh"

class Vector3 {
public :

    double x = 0;
    double y = 0;
    double z = 0;

    Vector3() = default;

    Vector3(double a, double b, double c) {
        this->x = a;
        this->y = b;
        this->z = c;
    }

    Vector3 operator*(const int &l) const {
        return Vector3(l*this->x, l*this->y, l*this->z);
    }
    Vector3 operator*(const double &l) const {
        return Vector3(l*this->x, l*this->y, l*this->z);
    }
    Vector3 operator/(const double &l) const {
        return Vector3(this->x/l, this->y/l, this->z/l);
    }
    Vector3 operator-(const Vector3 &v) const {
        return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
    }
    Vector3 operator+(const Vector3 &v) const {
        return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
    }
    Vector3 operator+(const double &d) const {
        return Vector3(this->x + d, this->y + d, this->z + d);
    }

    Vector3 operator-() const {
        return Vector3(-this->x, -this->y, -this->z);
    }

    double dot(const Vector3 &v) const {
        return this->x*v.x + this->y*v.y + this->z*v.z;
    }

    Vector3 cross(const Vector3 &v) const {
        return Vector3(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x);
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return this->x*this->x + this->y*this->y + this->z*this->z;
    }

    std::ostream& operator<<(std::ostream &out) const {
        out << "(" << this->x << ", " << this->y << ", " << this->z << ")";
        return out;
    }
    
    Vector3 direction() const {
        return *this/this->length();
    }

    // remets chaque composante entre 0 et 1 proportionnellement à la plus grande valeur
    Vector3 max_clamp() const {
        double max = std::max(std::max(this->x, this->y), this->z);
        return Vector3(this->x/max, this->y/max, this->z/max).clamp();
    }

    
    Vector3 clamp() const {
        return Vector3(std::min(1.0, std::max(0.0, this->x)), std::min(1.0, std::max(0.0, this->y)), std::min(1.0, std::max(0.0, this->z)));
    }

    Vector3 max_normalize() const {
        double max = std::max(std::max(this->x, this->y), this->z);
        return Vector3(this->x/max, this->y/max, this->z/max);
    }

    Vector3 normalize() const {
        double norme = std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        return Vector3(this->x / norme, this->y / norme, this->z / norme);
    }

    Vector3 mult(Vector3 v) const {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }

};


Vector3 nul = Vector3(0.0, 0.0, 0.0);

Vector3 get_ortho(Vector3& u, Vector3& v = nul) {
    if (v.length_squared() == 0) {      // Si on ne rentre rien pour V
        // Produit vectoriel avec un axe au pif (Axe X)
        Vector3 ortho = u.cross(Vector3(1.0, 0.0, 0.0));
        if (ortho.length_squared() == 0) {
            // If u is parallel to the x-axis, use the y-axis.
            ortho = u.cross(Vector3(0.0, 1.0, 0.0));
        }
        return ortho.normalize();
    } else {
        // If v is provided, find the orthogonal vector to both u and v.
        Vector3 ortho = u.cross(v);
        return ortho.normalize();
    }
}

using Point3 = Vector3;
using Color = Vector3;