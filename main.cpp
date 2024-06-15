#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define WINDOW_SIZE 500
#define COLOR 265

namespace
{
    const std::string MandelbrotStr = "mandelbrot";
}

enum class FractalType
{
    Mandelbrot = 1,
};

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

class Fractal
{
public:
    Fractal()
    {
        reset();
    }

    Fractal(const Fractal&) = delete;
    Fractal(Fractal&&) = delete;
    Fractal& operator=(const Fractal&) = delete;
    Fractal& operator=(Fractal&&) = delete;
    ~Fractal()
    {}

    void reset()
    {
        _type = FractalType::Mandelbrot;
        _zoom = WINDOW_SIZE / 4;
        _mouseX = 0;
        _mouseY = 0;
        _offsetX = -2;
        _offsetY = -2;
        _isJuliaLocked = false;
        _color = COLOR;
    }

    void setFractalType(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        if (str == MandelbrotStr)
            _type = FractalType::Mandelbrot;
        else
            showHelpMessage();
    }

private:
	double      _zoom;
	double      _mouseX;
	double      _mouseY;
	double      _offsetX;
	double      _offsetY;
	u_int32_t   _color;
	FractalType _type;
	bool        _isJuliaLocked;
};




class Engine final
{
public:
    Engine() = default;
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

    ~Engine()
    {}

    void init(int argc, char **argv)
    {
        if (argc == 2)
            _fractal.setFractalType(argv[1]);

        _image = new sf::Image();
        _image->create(WINDOW_SIZE, WINDOW_SIZE, sf::Color::White);
        _texture = new sf::Texture();
        _texture->loadFromImage(*_image);
        _window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "TEST");
        _sprite = new sf::Sprite();
        _sprite->setTexture(*_texture);
    }

    void reset()
    {
        _fractal.reset();
    }

// TODO: Change to private
public:
    Fractal _fractal;
    sf::Image* _image;
    sf::Texture* _texture;
    sf::RenderWindow* _window;
    sf::Sprite* _sprite;
};

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 2)
		showHelpMessage();

    Engine engine;
    engine.init(argc, argv);


    // ################### TESTING #####################
    engine._image->setPixel(400, 300, sf::Color::Red);
    engine._image->setPixel(400, 301, sf::Color::Red);
    engine._image->setPixel(400, 302, sf::Color::Red);
    engine._image->setPixel(400, 303, sf::Color::Red);
    engine._image->setPixel(400, 304, sf::Color::Red);
    engine._image->setPixel(400, 305, sf::Color::Red);
    engine._texture->loadFromImage(*engine._image);
    engine._sprite->setTexture(*engine._texture);

    sf::RenderWindow* window = engine._window;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(*engine._sprite);
        window->display();
    }
    return 0;
}
