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
    switch (key)
    {
    case sf::Keyboard::Up:
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
    case sf::Keyboard::Escape:
        _window.close();
        break;
    default:
        break;
    }
}

void Engine::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        _window.close();
        break;
    case sf::Event::MouseWheelScrolled:
        handleMouseWheelScrolledEvent(event);
        break;
    case sf::Event::KeyPressed:
        handleKeyPressedEvent(event.key.code);
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