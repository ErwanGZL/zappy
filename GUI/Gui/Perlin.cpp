/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Perlin
*/

#include "Perlin.hpp"

Perlin::Perlin(int width, int height)
{
    _width = width;
    _height = height;
}

Perlin::~Perlin()
{
}

void Perlin::genPermutation()
{
    permutation.resize(256);
    for (int i = 0; i < 256; i++)
        permutation[i] = i;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> distribution(0, 255);
    for (int i = 0; i < 256; i++) {
        int j = distribution(engine);
        int temp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = temp;
    }
    permutation.insert(permutation.end(), permutation.begin(), permutation.end());
}

double Perlin::fade(double t) const
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::lerp(double t, double a, double b) const
{
    return a + t * (b - a);
}

double Perlin::grad(int hash, double x, double y) const
{
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : h == 12 || h == 14 ? x : 0;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double Perlin::noise(double x, double y) const
{
    int X = static_cast<int>(floor(x)) & 255;
    int Y = static_cast<int>(floor(y)) & 255;

    x -= floor(x);
    y -= floor(y);

    double u = fade(x);
    double v = fade(y);

    int A = permutation[X] + Y;
    int AA = permutation[A];
    int AB = permutation[A + 1];
    int B = permutation[X + 1] + Y;
    int BA = permutation[B];
    int BB = permutation[B + 1];

    return lerp(v, lerp(u, grad(permutation[AA], x, y),
                             grad(permutation[BA], x - 1, y)),
                   lerp(u, grad(permutation[AB], x, y - 1),
                             grad(permutation[BB], x - 1, y - 1)));
}

double Perlin::octaveNoise(double x, double y) const
{
    double total = 0;
    double frequency = 1;
    double amplitude = 1;
    double maxValue = 0;

    for (int i = 0; i < _octave; i++) {
        total += noise(x * frequency, y * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= _persistence;
        frequency *= _lacunarity;
    }
    return total / maxValue;
}


std::vector<std::vector<int>> Perlin::run()
{
    genPermutation();
    std::vector<std::vector<double>> perlin;
    perlin.resize(_height);
    for (int i = 0; i < _height; i++)
        perlin[i].resize(_width);
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            perlin[i][j] = octaveNoise((double)j / (double)_width, (double)i / (double)_height);
        }
    }
    bool valid = false;
    std::vector<std::vector<int>> result = std::vector<std::vector<int>>(_height, std::vector<int>(_width, 0));
    for (int x = 0; x < _height; ++x) {
        for (int y = 0; y <_width ; ++y) {
            int tmp = (perlin[x][y] + 1) * 128;
            tmp = tmp * 3 / 255;
            if (tmp == 0)
                valid = true;
            result[x][y] = tmp;
        }
    }
    if (valid == false)
        return run();
    else
        return result;
}
