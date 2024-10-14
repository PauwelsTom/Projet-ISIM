#pragma once

#include "raymarcher.hh"
#include "object.hh"

class Object_list {
    public:
        Object_list() {}
        Object_list(std::shared_ptr<Object> object) { add(object); }

        void clear() { objects.clear(); }


        //? Ajoute un objet a la liste des objets
        void add(std::shared_ptr<Object> object) {
            objects.push_back(object);
        }


        //? Retourne la distance minimum parmis tous les objets
        double distance_min(Point3 p) const {
            double distance = -1;
            for (const auto& obj : objects) {
                if (distance == -1 || obj->distance(p) < distance) {
                    distance = obj->distance(p);
                }
            }
            return distance;
        }


        //? Renvoie l'objet le plus proche 
        std::shared_ptr<Object> get_closest_object(Point3 p) const {
            double distance = -1;
            std::shared_ptr<Object> closest_obj;
            for (const auto& obj : objects) {
                if (distance == -1 || obj->distance(p) < distance) {
                    distance = obj->distance(p);
                    closest_obj = obj;
                }
            }
            return closest_obj;
        }


        //? Renvoie la normale a l'objet qui est rencontre
        Vector3 get_normal(Point3 p) const {
            std::shared_ptr<Object> obj = get_closest_object(p);
            return obj->get_normal(p);
        }


        //? Renvoie le material
        std::shared_ptr<Material> get_material(Point3 p) const {
            std::shared_ptr<Object> obj = get_closest_object(p);
            return obj->material;
        }


        //? Fais la fonction shade sur l'element que rencontre le rayon
        Color shade(const Ray& _ray, const Vector3& _point, const Vector3& _normal) const {
            std::shared_ptr<Object> obj = get_closest_object(_point);
            return obj->shade(_ray, _point, _normal);
        } 

    private:
        std::vector<std::shared_ptr<Object>> objects;
};