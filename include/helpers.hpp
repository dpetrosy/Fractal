#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <SFML/Graphics.hpp>
#include <string>

// Application defines
#define APP_NAME "Fractal"
#define THREADS_COUNT 40
#define WINDOW_SIZE 800
#define MAX_ITER 1000
#define ZOOM 1.3
#define VIEW_CHANGE_SIZE (WINDOW_SIZE / 15)

// Mandelbox fractal defines
#define SCALE 2
#define FIXED_RADIUS 1
#define MINIMUM_RADIUS 0.5

// Red
#define RED 21
#define GREEN 0
#define BLUE 0

// Cyan
// #define RED 0
// #define GREEN 21
// #define BLUE 21

// Yellow
// #define RED 21
// #define GREEN 21
// #define BLUE 0

// Magenda
// #define RED 21
// #define GREEN 0
// #define BLUE 21

// Gray
// #define RED 21
// #define GREEN 21
// #define BLUE 21

// Dark Purple
// #define RED 48
// #define GREEN 25
// #define BLUE 52

// Mediumblue
// #define RED 0
// #define GREEN 0
// #define BLUE 205

namespace
{
    const std::string MandelbrotStr = "mandelbrot";
    const std::string JuliaStr = "julia";
    const std::string BurningShipStr = "burning_ship";
    const std::string TricornStr = "tricorn";
    const std::string MandelboxStr = "mandelbox";
    const std::string MultibrotStr = "multibrot";
    const std::string MandelbarStr = "mandelbar";
    const std::string PerBurningShipStr = "per_burning_ship";
    const std::string CelticMandelbrotStr = "celtic_mandelbrot";
}

enum class FractalType
{
    Mandelbrot = 1,
    Julia = 2,
    BurningShip = 3,
    Tricorn = 4,
    Mandelbox = 5,
    Multibrot = 6,
    Mandelbar = 7,
    PerBurningShip = 8,
    CelticMandelbrot = 9,
};

struct ComplexNumber
{
    double re = 0.0;
    double im = 0.0;
    double reJulia = 0.0;
    double imJulia = 0.0;
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

// Util functions
void showHelpMessage();
bool isArgsValid(int argc, char **argv);
int  getRandomValue(int start, int end);

// Fractal calculating functions
size_t calcMandelbrot(ComplexNumber& c);
size_t calcJulia(ComplexNumber& c);
size_t calcBurningShip(ComplexNumber& c);
size_t calcTricorn(ComplexNumber& c);
size_t calcMandelbox(ComplexNumber& c);
size_t calcMultibrot(ComplexNumber& c);
size_t calcMandelbar(ComplexNumber& c);
size_t calcPerBurningShip(ComplexNumber& c);
size_t calcCelticMandelbrot(ComplexNumber& c);

class Fractal;
void colorizePixelsByGPU(sf::Image& image, Fractal& fractal);

#endif  /* HELPERS_HPP */