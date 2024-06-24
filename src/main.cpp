#include <iostream>
#include "engine.hpp"

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

int main(int argc, char **argv) try
{
    if (!isArgsValid(argc, argv))
        showHelpMessage();

    Engine& engine = Engine::getInstance();
    if (argc == 2)
        engine.setFractalType(argv[1]);

    sf::Event event;
    sf::RenderWindow& window = engine.getWindow();
    engine.draw();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
            engine.handleEvent(event);
    }
    return 0;
}
catch(const std::exception& e)
{
    std::cerr << e.what() << std::endl;
}
catch(...)
{
    std::cerr << "-- Unknown exception was caught." << std::endl;
}