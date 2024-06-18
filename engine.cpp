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