#pragma once

#include "camera.hh"
#include "image.hh"
#include "object_list.hh"
#include "hitRecord.hh"

#include <memory>
#include <thread>

class Light {
public:
    Point3 position;
    Color intensity;

    Light(const Point3& position, const Color& intensity) : position(position), intensity(intensity) {}

    virtual ~Light() {}  // Ajout d'un destructeur virtuel
};

class AreaLight : public Light {
public:
    Vector3 u, v;

    AreaLight(const Point3& position, const Color& intensity, const Vector3& u, const Vector3& v)
        : Light(position, intensity), u(u), v(v) {}

    // Méthode pour générer un point aléatoire dans la zone de lumière
    Point3 randomPoint() const {
        return position + u * random_double() * 2 + v * random_double() * 3;
    }
};

class Scene {
public:
    Object_list world;
    std::vector<std::shared_ptr<Light>> lights;

    Scene() {}
    Scene(const Object_list& world, const std::vector<std::shared_ptr<Light>>& lights) : world(world), lights(lights) {}

    double distance(const Point3& p) const {
        return world.distance_min(p);
    }

    std::shared_ptr<Object> get_closest_object(const Point3& p) const {
        return world.get_closest_object(p);
    }

    HitRecord getHitRecord(Point3 currentPoint, Ray ray) {
        double t = 0.0;
        double minDist = distance(currentPoint);
        for (int i = 0; i < 100; ++i) {
            currentPoint = ray.origin_ + ray.direction_ * t;
            double dist = distance(currentPoint);
            if (dist < minDist) {
                minDist = dist;
            }
            if (dist < 0.00001) {
                Vector3 normal = world.get_normal(currentPoint);
                return HitRecord(t, currentPoint, ray, normal, world.get_material(currentPoint), true);
            }
            t += dist;
        }
        return HitRecord();
    }

    Color computeLighting(const Point3& point, const Vector3& normal) const {
        Color color(0.0, 0.0, 0.0);
        const int nb_sample = 10;
        for (const auto& light : lights) {
            if (auto areaLight = std::dynamic_pointer_cast<AreaLight>(light)) {
                for (int i = 0; i < nb_sample; ++i) {
                    Point3 samplePoint = areaLight->randomPoint();
                    Light sampleLight(samplePoint, light->intensity * (1.0 / nb_sample));
                    if (!isInShadow(point, sampleLight)) {
                        Vector3 lightDir = (samplePoint - point).normalize();
                        double diff = std::max(0.0, normal.dot(lightDir));
                        color = color + sampleLight.intensity * diff;
                    }
                }
            } else {
                if (!isInShadow(point, *light)) {
                    Vector3 lightDir = (light->position - point).normalize();
                    double diff = std::max(0.0, normal.dot(lightDir));
                    color = color + light->intensity * diff;
                }
            }
        }
        return color;
    }

    Color computeLighting2(const Point3& point, const Vector3& normal) const {
        Color color(0.0, 0.0, 0.0);
        const int nb_sample = 10;
        for (const auto& light : lights) {
            Vector3 versLumiere = light->position - point;
            Vector3 u = get_ortho(versLumiere);
            Vector3 v = get_ortho(versLumiere, u);

            AreaLight areaLight = AreaLight(light->position, light->intensity, u, v);

            for (int i = 0; i < nb_sample; ++i) {
                Point3 samplePoint = areaLight.randomPoint();
                Light sampleLight(samplePoint, light->intensity * (1.0 / nb_sample));
                if (!isInShadow(point, sampleLight)) {
                    Vector3 lightDir = (samplePoint - point).normalize();
                    double diff = std::max(0.0, normal.dot(lightDir));
                    color = color + sampleLight.intensity * diff;
                }
            }
        }
        return color;
    }

    bool isInShadow(const Point3& point, const Light& light, const double dist_min=0.00001, const int max_iter=100) const {
        Vector3 lightDir = (light.position - point).normalize();
        double lightDistance = (light.position - point).length();
        Ray shadowRay(point + lightDir * dist_min, lightDir);  // Small offset to avoid self-intersection

        double dTot = 0.0;
        for (int i = 0; i < max_iter; ++i) {
            Point3 currPoint = shadowRay.origin_ + shadowRay.direction_ * (dTot + lightDistance / 10.0);
            double dScene = distance(currPoint);
            dTot += dScene;

            if (dScene < dist_min) {
                return true;  // There is an object blocking the light
            }
            if (dTot > lightDistance) {
                return false;  // The light source is reached without intersections
            }
        }
        return false;
    }

};
