#include "engine.hpp"

Engine::Engine()
{
    _image.create(WINDOW_SIZE, WINDOW_SIZE, sf::Color::Black);
    _window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), APP_NAME);
}

Engine::~Engine()
{}

Engine* Engine::getInstance()
{
    if (_engine == nullptr)
        _engine = new Engine();
    return _engine;
}

Engine* Engine::_engine = nullptr;

void Engine::draw()
{
    _window.clear();
    _texture.loadFromImage(_image);
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