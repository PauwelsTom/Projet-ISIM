#pragma once

#include "raymarcher.hh"
#include "scene.hh"

// Fonction pour générer un double aléatoire entre 0 et 1
double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

class Material {
public:
    virtual Color shade(const Ray& ray, const Vector3& point, const Vector3& normal) const = 0;
};


class Natural : public Material {
public:
    Color albedo;

    Natural(const Color& albedo) : albedo(albedo) {}

    Color shade(const Ray& ray, const Vector3& point, const Vector3& normal) const {
        return albedo;
    }
};


class Lambertian : public Material {
public:
    Color albedo;

    Lambertian(const Color& albedo) : albedo(albedo) {}

    Color shade(const Ray& ray, const Vector3& point, const Vector3& normal) const {
        double diffuse = std::max(0.0, normal.dot(-ray.direction_));
        return albedo * diffuse;
    }
};


class Reflect : public Material {
    public:
    Color albedo;

    Reflect(const Color& albedo) : albedo(albedo) {}

    Color shade(const Ray& ray, const Vector3& point, const Vector3& normal) const {

        // Calculer la direction du rayon réfléchi
        const double temp = ray.direction_.dot(normal);
        Vector3 reflectedDirection = ray.direction_ - normal * 2.0 * temp;
        Ray reflectedRay(point, reflectedDirection);

        // Lancer le rayon réfléchi pour obtenir la couleur de l'environnement
        // TODO : Color reflectedColor = rayMarch(reflectedRay, /* SCENE */);

        // Combiner la couleur réfléchie avec l'albedo
        // TODO : Color finalColor = (reflectedColor + albedo) * 0.5;   -> a decommenter
        // TODO : return finalColor;

        return albedo;
    }
};


class Metal : public Material {
public:
    Color albedo;
    double fuzz;

    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    Color shade(const Ray& ray, const Vector3& point, const Vector3& normal) const {
        Vector3 reflected = reflect(ray.direction_, normal);
        Ray scattered(point, reflected + random_in_unit_sphere() * fuzz);
        if (scattered.direction_.dot(normal) > 0) {
            return albedo * std::max(0.0, normal.dot(-scattered.direction_));
        }
        return Color(0, 0, 0);
    }

private:
    Vector3 reflect(const Vector3& v, const Vector3& n) const {
        return v - n * 2 * v.dot(n);
    }

    Vector3 random_in_unit_sphere() const {
        Vector3 p;
        do {
            p = Vector3(random_double(), random_double(), random_double()) * 2.0 - Vector3(1, 1, 1);
        } while (p.length() >= 1.0);
        return p;
    }
};
