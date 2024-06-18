#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>

#define APP_NAME "Fractal"
#define WINDOW_SIZE 1000
#define COLOR 265
#define MAX_ITER 200

namespace
{
    const std::string MandelbrotStr = "mandelbrot";
    const std::string JuliaStr = "julia";
    const std::string BurningShipStr = "burning_ship";
}

enum class FractalType
{
    Mandelbrot = 1,
    Julia = 2,
    Burning_Ship = 3,
};

struct ComplexNumber
{
    double re = 0.0;
    double im = 0.0;
};

void showHelpMessage();

#endif  /* HELPERS_HPP */