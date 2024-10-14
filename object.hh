#pragma once

#include "raymarcher.hh"
#include "material.hh"


//! Classe abstraite pour regrouper les objets
class Object {
    public:
        virtual ~Object() = default;

        std::shared_ptr<Material> material;

        virtual double distance(const Point3& p) const = 0;
        virtual Vector3 get_normal(const Point3& p) const = 0;
        
        Color shade(const Ray& _ray, const Vector3& _point, const Vector3& _normal) const {
            return material->shade(_ray, _point, _normal);
        } 
};


//! Classe : Sphere(centre, rayon, matiere)
class Sphere : public Object {
    public:
        Sphere(Point3 _center, double _radius, std::shared_ptr<Material> _material): center(_center), radius(_radius) {  material = _material; }

        double distance(const Point3& p) const {
            return (p - center).length() - radius;
        }

        Vector3 get_normal(const Point3& p) const {
            return (p - center).normalize();
        }

    private:
        Point3 center;
        double radius;
};


//! Classe : Plan
class Plane : public Object {
    public:
        Plane(const Vector3& _normal, double _d, std::shared_ptr<Material> _material): normal(_normal), d(_d) { material = (_material); }

        double distance(const Point3& p) const {
            return p.dot(normal) - d;
        }

        Vector3 get_normal(const Point3& p) const {
            return normal;
        }

    private:
        Vector3 normal; // Vecteur de la normale au plan
        double d;       // Distance par rapport a la camera
};