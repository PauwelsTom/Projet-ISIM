#pragma once

#include "raymarcher.hh"

class Image {
public:
    int width_;
    int height_;
    std::vector<std::vector<Color>> pixels_;

    Image(int width, int height, std::vector<std::vector<Color>> pixels) : width_(width), height_(height), pixels_(std::move(pixels)) {
        
    }

    void setPixel(int x, int y, double red, double green, double blue) {
        int index = y * width_ + x;
        pixels_[x][y] = Color(red, green, blue);
    }

    void savePPM(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
            return;
        }

        file << "P3\n";
        file << width_ << " " << height_ << "\n";
        file << "255\n";

        for (int j = 0; j < height_; ++j) {
            for (int i = 0; i < width_; ++i) {
                file << static_cast<int>(pixels_[i][j].x*255.99) << " "
                    << static_cast<int>(pixels_[i][j].y*255.99) << " "
                    << static_cast<int>(pixels_[i][j].z*255.99) << "\n";

            }
        }
        file.close();
        std::cout << "Image enregistrée sous " << filename << std::endl;
    }

};