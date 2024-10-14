#pragma once

#include <memory>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <fstream>
#include <cstdlib>

#include "vector3.hh"
#include "ray.hh"
#include "image.hh"
#include "camera.hh"
#include "scene.hh"
#include "material.hh"
#include "object.hh"
#include "object_list.hh"

//#include ""

Color rayMarch(const Ray& ray, const Scene& scene, double maxDist = 100.0, double minDist = 0.001, int maxSteps = 100) {
    double dTot = 0.0;

    for (int i = 0; i < maxSteps; ++i) {
        Point3 currPoint = ray.origin_ + ray.direction_ * dTot;
        double dScene = scene.distance(currPoint);
        dTot += dScene;

        if (dScene < minDist) {
            Vector3 normal = scene.world.get_normal(currPoint);
            
            Color materialColor = scene.world.shade(ray, currPoint, normal);
            Color lightColor = scene.computeLighting2(currPoint, normal);
            return materialColor.mult(lightColor);
        }
        if (dTot > maxDist) {
            break;
        }
    }
    return Color(0.0, 0.0, 0.0);
}

void renderPart(int startY, int endY, const Camera& camera, const Scene& scene, Image& image, int samples_per_pixel) {
    for (int j = startY; j < endY; ++j) {
        for (int i = 0; i < image.width_; ++i) {
            Color pixel_color(0.0, 0.0, 0.0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (i + random_double()) / image.width_;
                double v = (j + random_double()) / image.height_;
                Ray ray = camera.getRay(u, v);
                pixel_color = pixel_color + rayMarch(ray, scene);
            }
            pixel_color = pixel_color * (1.0 / samples_per_pixel); // Moyenne des couleurs
            image.setPixel(i, j, pixel_color.x, pixel_color.y, pixel_color.z);
        }
    }
}

void render(const Camera& camera, const Scene& scene, Image& image, int samples_per_pixel, int num_threads) {
    std::vector<std::thread> threads;
    int part_height = image.height_ / num_threads;

    for (int t = 0; t < num_threads; ++t) {
        int startY = t * part_height;
        int endY = (t == num_threads - 1) ? image.height_ : (t + 1) * part_height;
        threads.push_back(std::thread(renderPart, startY, endY, std::ref(camera), std::ref(scene), std::ref(image), samples_per_pixel));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

