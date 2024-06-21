#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define APP_NAME "Fractal"
#define WINDOW_SIZE 1000
#define COLOR 265
#define MAX_ITER 200
#define ZOOM 1.3
#define VIEW_CHANGE_SIZE (WINDOW_SIZE / 15)

#define RED 0
#define GREEN 1
#define BLUE 9

namespace
{
    const std::string MandelbrotStr = "mandelbrot";
    const std::string JuliaStr = "julia";
    const std::string BurningShipStr = "burning_ship";
    const std::string MultibrotStr = "multibrot";
    const std::string MandelbarStr = "mandelbar";
}

enum class FractalType
{
    Mandelbrot = 1,
    Julia = 2,
    BurningShip = 3,
    Tricorn = 4,
    Multibrot = 7,
    Mandelbar = 7,
};

struct ComplexNumber
{
    double re = 0.0;
    double im = 0.0;
};

struct RGBColor
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    RGBColor() = default;
    RGBColor(unsigned char red, unsigned char green, unsigned char blue)
        : r(red), g(green), b(blue) {}

    inline sf::Color toSFColor(size_t iter) const
    {
        return sf::Color(r * iter, g * iter, b * iter);
    }
};

#endif  /* HELPERS_HPP */