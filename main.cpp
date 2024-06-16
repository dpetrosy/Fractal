#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define APP_NAME "Fractal"
#define WINDOW_SIZE 1000
#define COLOR 265
#define MAX_ITER 2000

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

struct ComplexNumber
{
    double re = 0.0;
    double im = 0.0;
};

int	calcMandelbrot(ComplexNumber& c)
{
	double        reTemp;
	ComplexNumber z;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.re * z.im + c.im;
		z.re = reTemp;
	}
	return (i);
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
        fractalCallback = calcMandelbrot;
    }

    void setFractalType(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        if (str == MandelbrotStr)
            _type = FractalType::Mandelbrot;
        else
            showHelpMessage();
    }

    size_t calc(ComplexNumber& c)
    {
        return fractalCallback(c);
    }

    double getZoom()
    {
        return _zoom;
    }

    double getOffsetX()
    {
        return _offsetX;
    }

    double getOffsetY()
    {
        return _offsetY;
    }

    u_int32_t getColor()
    {
        return _color;
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
    std::function<size_t(ComplexNumber&)> fractalCallback;
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
        _image.create(WINDOW_SIZE, WINDOW_SIZE, sf::Color::White);
        _window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), APP_NAME);
        _texture.loadFromImage(_image);
        _sprite.setTexture(_texture);
    }

    void draw()
    {
        _window.clear();
        _texture.loadFromImage(_image);
        _sprite.setTexture(_texture);
        _window.draw(_sprite);
        _window.display();
    }

    Fractal& getFractal()
    {
        return _fractal;
    }

    sf::Image& getImage()
    {
        return _image;
    }

    sf::RenderWindow& getWindow()
    {
        return _window;
    }

private:
    Fractal          _fractal;
    sf::Image        _image;
    sf::Texture      _texture;
    sf::Sprite       _sprite;
    sf::RenderWindow _window;
};

void calcFractal(Engine& engine) try
{
    size_t iter;
	ComplexNumber c;
    Fractal& fractal = engine.getFractal();
    double zoom = fractal.getZoom();
    double offsetX = fractal.getOffsetX();
    double offsetY = fractal.getOffsetY();

    for (int i = 0; i < WINDOW_SIZE; ++i)
    {
        c.re = (i / zoom) + offsetX;
        for (int j = 0; j < WINDOW_SIZE; ++j)
        {
            c.im = (j / zoom) + offsetY;
            iter = fractal.calc(c);
            engine.getImage().setPixel(i, j, sf::Color(iter, 0, 0));
        }
    }
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 2)
		showHelpMessage();

    Engine* engine = new Engine();
    engine->init(argc, argv);

    calcFractal(*engine);
    sf::RenderWindow& window = engine->getWindow();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // calcFractal(*engine);
        engine->draw();
    }
    return 0;
}
