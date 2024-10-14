#pragma once

#include "vector3.hh"
#include "ray.hh"
#include "material.hh"
#include <memory>

class HitRecord {
public:
    double distance; // Distance du rayon par rapport a l'objet rencontre (t = 0 si le rayon touche l'objet)
    Point3 position;
    Vector3 normal;
    Ray ray;
    bool hitSomething = false;
    std::shared_ptr<Material> material;

    HitRecord() = default;

    HitRecord(double t, const Point3& p, const Ray& ray, const Vector3& normal, std::shared_ptr<Material> material, bool hitSomething) : distance(t), position(p), ray(ray), normal(normal), material(material), hitSomething(hitSomething) {}
};