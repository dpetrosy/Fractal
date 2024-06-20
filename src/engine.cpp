// #include <SFML/OpenGL.hpp>
// #include <GL/gl.h>
#include "engine.hpp"

Engine::Engine()
{
    _image.create(WINDOW_SIZE, WINDOW_SIZE, sf::Color::Black);
    if (!_texture.loadFromImage(_image))
        throw std::runtime_error("Failed to create SFML image.\nTerminating the program...");
    _window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), APP_NAME);
    if (!_window.isOpen())
        throw std::runtime_error("Failed to crate SFML window.\nTerminating the program...");
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
    _window.clear();
    if (!_texture.loadFromImage(_image))
        throw std::runtime_error("Failed to set pixel on image.\nTerminating the program...");
    _sprite.setTexture(_texture);
    _window.draw(_sprite);
    _window.display();

    // if (glGetError() != GL_NO_ERROR)
    //     throw std::runtime_error("Caught error from OpenGL, \
    //     can't draw on window.\nTerminating the program...");
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
    case sf::Event::Closed:
        _window.close();
        break;
    default:
        break;
    }

    if (event.type == sf::Event::MouseWheelScrolled || 
        event.type == sf::Event::KeyPressed)
    {
        _fractal.colorizePixels(_image);
        draw();
    }
}

void Engine::handleKeyPressedEvent(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Down ||
        key == sf::Keyboard::Left || key == sf::Keyboard::Right)
        handleViewChangeEvent(key);
    else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
        handleFractalChangeEvent(key);
    else if (key == sf::Keyboard::Escape)
        _window.close();
    //else // Color change keys
        // HandleColorChangeEvent(key);
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
    case sf::Keyboard::Num1:
        _fractal.setFractalType(MandelbrotStr);
        break;
    case sf::Keyboard::Num2:
        _fractal.setFractalType(JuliaStr);
        break;
    case sf::Keyboard::Num3:
        _fractal.setFractalType(BurningShipStr);
        break;
    default:
        break;
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

void Engine::setFractalType(const std::string& type)
{
    _fractal.setFractalType(type);
}

Fractal& Engine::getFractal()
{
    return _fractal;
}

sf::Image& Engine::getImage()
{
    return _image;
}

sf::RenderWindow& Engine::getWindow()
{
    return _window;
}