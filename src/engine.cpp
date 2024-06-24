#include "engine.hpp"

Engine::Engine()
{
    _image.create(WINDOW_SIZE, WINDOW_SIZE, sf::Color::Black);
    if (!_texture.loadFromImage(_image))
        throw std::runtime_error("-- Failed to create SFML image.\n-- Terminating the program...");
    _window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), APP_NAME);
    if (!_window.isOpen())
        throw std::runtime_error("-- Failed to crate SFML window.\n-- Terminating the program...");
}

Engine::~Engine()
{}

Engine& Engine::getInstance()
{
    static Engine engine;
    return engine;
}

void Engine::draw()
{
    _fractal.colorizePixels(_image);
    _window.clear(sf::Color::Black);
    if (!_texture.loadFromImage(_image))
        throw std::runtime_error("-- Failed to set pixel on image.\n-- Terminating the program...");
    _sprite.setTexture(_texture);
    _window.draw(_sprite);
    _window.display();
}

void Engine::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::MouseWheelScrolled:
        handleMouseWheelScrolledEvent(event);
        break;
    case sf::Event::KeyPressed:
        handleKeyPressedEvent(event.key.code);
        break;
    case sf::Event::MouseMoved:
        handleMouseMovedEvent(event);
        break;
    case sf::Event::Closed:
        _window.close();
        break;
    default:
        break;
    }

    if (event.type == sf::Event::MouseWheelScrolled ||
        event.type == sf::Event::KeyPressed ||
        (_fractal.isNeedToHandleMouseMoved() &&
        event.type == sf::Event::MouseMoved))
    {
        draw();
    }
}

void Engine::handleMouseWheelScrolledEvent(const sf::Event& event)
{
    int x = event.mouseWheelScroll.x;
    int y = event.mouseWheelScroll.y;

    if (event.mouseWheelScroll.delta > 0) // Zoom-in
        _fractal.zoomIn(x, y);
    else // Zoom-out
        _fractal.zoomOut(x, y);
}

void Engine::handleKeyPressedEvent(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Down ||
        key == sf::Keyboard::Left || key == sf::Keyboard::Right)
        handleViewChangeEvent(key);
    else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
        handleFractalChangeEvent(key);
    else if (key == sf::Keyboard::L)
        _fractal.switchJuliaLock();
    else if (key == sf::Keyboard::Escape)
        _window.close();
    else // Color change keys
        handleColorChangeEvent(key);
}

void Engine::handleViewChangeEvent(sf::Keyboard::Key key)
{
    switch (key)
    {
    case (sf::Keyboard::Up):
        _fractal.moveViewUp();
        break;
    case sf::Keyboard::Down:
        _fractal.moveViewDown();
        break;
    case sf::Keyboard::Left:
        _fractal.moveViewLeft();
        break;
    case sf::Keyboard::Right:
        _fractal.moveViewRight();
        break;
    default:
        break;
    }
}

void Engine::handleFractalChangeEvent(sf::Keyboard::Key key)
{
    _fractal.reset();

    switch (key)
    {
    case sf::Keyboard::Num0:
        _fractal.setColor(RED, GREEN, BLUE);
        break;
    case sf::Keyboard::Num1:
        _fractal.setFractalType(MandelbrotStr);
        _window.setTitle("Mandelbrot");
        break;
    case sf::Keyboard::Num2:
        _fractal.setFractalType(JuliaStr);
        _window.setTitle("Julia");
        break;
    case sf::Keyboard::Num3:
        _fractal.setFractalType(BurningShipStr);
        _window.setTitle("Burning Ship");
        break;
    case sf::Keyboard::Num4:
        _fractal.setFractalType(TricornStr);
        _window.setTitle("Tricorn");
        break;
    case sf::Keyboard::Num5:
        _fractal.setFractalType(MandelboxStr);
        _window.setTitle("Mandelbox");
        break;
    case sf::Keyboard::Num6:
        _fractal.setFractalType(MultibrotStr);
        _window.setTitle("Multibrot");
        break;
    case sf::Keyboard::Num7:
        _fractal.setFractalType(MandelbarStr);
        _window.setTitle("Mandelbar");
        break;
    case sf::Keyboard::Num8:
        _fractal.setFractalType(PerBurningShipStr);
        _window.setTitle("Perpendicular Burning Ship");
        break;
    case sf::Keyboard::Num9:
        _fractal.setFractalType(CelticMandelbrotStr);
        _window.setTitle("Celtic Mandelbrot");
        break;
    default:
        break;
    }
}

void Engine::handleColorChangeEvent(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::R:
        _fractal.changeColor(1, 0, 0);
        break;
    case sf::Keyboard::G:
        _fractal.changeColor(0, 1, 0);
        break;
    case sf::Keyboard::B:
        _fractal.changeColor(0, 0, 1);
        break;
    case sf::Keyboard::C:
        _fractal.setColor(getRandomValue(0, 255),
            getRandomValue(0, 255), getRandomValue(0, 255));
        break;
    default:
        break;
    }
}

void Engine::handleMouseMovedEvent(const sf::Event& event)
{
    _fractal.setMouseCoords(event.mouseMove.x, event.mouseMove.y);
}

Fractal& Engine::getFractal()
{
    return _fractal;
}

sf::RenderWindow& Engine::getWindow()
{
    return _window;
}