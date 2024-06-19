#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "fractal.hpp"

class Engine final
{
public:
    static Engine* getInstance();

    void draw();
    void handleMouseWheelScrolledEvent(const sf::Event& event);
    void handleKeyPressedEvent(sf::Keyboard::Key key);
    void handleEvent(const sf::Event& event);

    void setFractalType(const std::string& type);

    Fractal& getFractal();
    sf::Image& getImage();
    sf::RenderWindow& getWindow();

private:
    Engine();
    ~Engine();

    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

private:
    static Engine*   _engine;
    Fractal          _fractal;
    sf::Image        _image;
    sf::Texture      _texture;
    sf::Sprite       _sprite;
    sf::RenderWindow _window;
};

#endif  /* ENGINE_HPP */