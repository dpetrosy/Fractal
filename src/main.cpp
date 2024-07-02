#include <iostream>
#include "engine.hpp"

int main(int argc, char **argv) try
{
    if (!isArgsValid(argc, argv))
        showHelpMessage();

    Engine& engine = Engine::getInstance();
    if (argc == 2)
        engine.getFractal().setFractalType(argv[1]);

    sf::Event event;
    engine.draw();
    sf::RenderWindow& window = engine.getWindow();

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
    std::cerr << "-- Terminating the program..." << std::endl;
}
catch(...)
{
    std::cerr << "-- Unknown exception was caught." << std::endl;
    std::cerr << "-- Terminating the program..." << std::endl;
}