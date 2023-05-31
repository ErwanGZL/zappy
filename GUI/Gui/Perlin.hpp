/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Perlin
*/

#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>

class Perlin {
    public:
        Perlin(int width, int height);
        ~Perlin();
        std::vector<std::vector<int>> run();
        double noise(double x, double y) const;
        double octaveNoise(double x, double y) const;
        void genPermutation();

    private:
        int _width;
        int _height;
        int _octave = 6;
        double _persistence = 0.2;
        double _lacunarity = 2.0;
        std::vector<int> permutation;


        double fade(double t) const;
        double lerp(double t, double a, double b) const;
        double grad(int hash, double x, double y) const;
};
