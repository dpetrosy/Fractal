#include <SFML/Graphics.hpp>
#include <algorithm>

#include "fractal.hpp"
#include "fractalUtils.hpp"

Fractal::Fractal()
{
    reset();
}

Fractal::~Fractal()
{}

void Fractal::reset()
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

void Fractal::colorizePixels(sf::Image& image)
{
    size_t iterCount;
	ComplexNumber c;

    for (int i = 0; i < WINDOW_SIZE; ++i)
    {
        c.re = i / _zoom + _offsetX;
        for (int j = 0; j < WINDOW_SIZE; ++j)
        {
            c.im = j / _zoom + _offsetY;
            iterCount = fractalCallback(c);
            image.setPixel(i, j, sf::Color(iterCount, 0, 0));
        }
    }
}

void Fractal::setFractalType(std::string type)
{
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == MandelbrotStr)
        _type = FractalType::Mandelbrot;
    else
        showHelpMessage();
}

double Fractal::getZoom()
{
    return _zoom;
}

double Fractal::getOffsetX()
{
    return _offsetX;
}

double Fractal::getOffsetY()
{
    return _offsetY;
}

u_int32_t Fractal::getColor()
{
    return _color;
}