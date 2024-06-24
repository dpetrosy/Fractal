#include <random>
#include "helpers.hpp"

void showHelpMessage()
{
	std::cout << R"(
    +------------------ Let me help you! ---------------------+
    |                                                         |
    | Usage: ./fractal [mandelbrot / julia / burning_ship /   |
    |                   tricorn / mandelbox / multibrot /     |
    |                   mandelbar / per_burning_ship /        |
    |                   celtic_mandelbrot]                    |
    |                                                         |
    | e.g: ./fractal mandelbrot                               |
    |                                                         |
    |----------------------- KEYBOARD ------------------------|
    |                                                         |
    | Press ESC to close the window                           |
    | Press one of [1-9] to change the fractal                |
    | Press R key to change the red component of fractal      |
    | Press G key to change the green component of fractal    |
    | Press B key to change the blue component of fractal     |
    | Use mouse scroll to zoom in and out of the fractal      |
    | Press the arrow keys to change the viewpoint            |
    | Press L to lock Julia's fractal                         |
    | Press Zero to reset the fractal                         |
    +---------------------------------------------------------+
        )" << std::endl;
	exit(EXIT_SUCCESS);
}

bool isArgsValid(int argc, char **argv)
{
    std::string type;

    if (argc == 1)
        return true;
    else if (argc == 2)
        type = argv[1];
    else
        return false;

    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type != MandelbrotStr && type != JuliaStr &&
        type != BurningShipStr && type != TricornStr &&
        type != MandelboxStr && type != MultibrotStr &&
        type != MandelbarStr && type != PerBurningShipStr &&
        type != CelticMandelbrotStr)
        return false;
    return true;
}

int getRandomValue(int start, int end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(start, end);
    return dis(gen);
}