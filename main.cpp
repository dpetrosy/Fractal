#include <iostream>

#include "engine.hpp"

void showHelpMessage()
{
	std::cout << R"(
        +------------------ Let me help you! ---------------------+
        |                                                         |
        | Usage: ./fractol [mandelbrot / julia / burning_ship     |
        |                   tricorn / mandelbox /                 |
        |                   celtic_mandelbar]                     |
        |                                                         |
        | e.g: ./fractol mandelbrot                               |
        |                                                         |
        |----------------------- KEYBOARD ------------------------|
        |                                                         |
        | Press ESC to close the window                           |
        | Press one of [1-6] to move to another fractal           |
        | Press one of [Q-Y] keys to change the color of fractal  |
        | Press one of [A-H] keys to change the color of fractal  |
        | Use mouse scroll to zoom in and out of the fractal      |
        | Press the arrow keys to change the viewpoint            |
        | Press L to lock Julia's fractal                         |
        | Press Zero to reset the fractal                         |
        +---------------------------------------------------------+
        )" << std::endl;
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 2)
		showHelpMessage();

    Engine* engine = Engine::getInstance();
    if (argc == 2)
        engine->setFractalType(argv[1]);

    sf::Event event;
    sf::RenderWindow& window = engine->getWindow();
    Fractal& fractal = engine->getFractal();
    fractal.colorizePixels(engine->getImage());
    engine->draw();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            engine->handleEvent(event);
			//std::cout << "HELLO\n";
            //fractal.colorizePixels(engine->getImage());
        }
    }
    return 0;
}
