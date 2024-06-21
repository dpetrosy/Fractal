#include <SFML/Graphics.hpp>
#include <algorithm>
#include "fractal.hpp"
#include "fractalUtils.hpp"

Fractal::Fractal()
{
    reset();
    setFractalType(MandelbrotStr);
}

Fractal::~Fractal()
{}

void Fractal::reset()
{
    _zoom = WINDOW_SIZE / 4;
    _mouseX = 0;
    _mouseY = 0;
    _offsetX = -2;
    _offsetY = -2;
    _isJuliaLocked = false;
    _color = RGBColor(RED, GREEN, BLUE);
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
            image.setPixel(i, j, _color.toSFColor(iterCount));
        }
    }
}

void Fractal::setFractalType(std::string type)
{
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == MandelbrotStr)
    {
        _type = FractalType::Mandelbrot;
        fractalCallback = calcMandelbrot;
    }
    else if (type == JuliaStr)
    {
        _type = FractalType::Julia;
        // fractalCallback = calcJulia;
    }
    else if (type == BurningShipStr)
    {
        _type = FractalType::BurningShip;
        fractalCallback = calcBurningShip;
    }
    else if (type == MandelbarStr)
    {
        _type = FractalType::Mandelbar;
        fractalCallback = calcMandelbar;
    }
}

void Fractal::zoomIn(int x, int y)
{
    _offsetX += x / _zoom - (x / (_zoom * ZOOM));
    _offsetY += y / _zoom - (y / (_zoom * ZOOM));
    _zoom *= ZOOM;
}

void Fractal::zoomOut(int x, int y)
{
    _offsetX += x / _zoom - (x / (_zoom / ZOOM));
    _offsetY += y / _zoom - (y / (_zoom / ZOOM));
    _zoom /= ZOOM;
}

void Fractal::moveViewUp()
{
    _offsetY -= VIEW_CHANGE_SIZE / _zoom;
}

void Fractal::moveViewDown()
{
    _offsetY += VIEW_CHANGE_SIZE / _zoom;
}

void Fractal::moveViewLeft()
{
    _offsetX -= VIEW_CHANGE_SIZE / _zoom;
}

void Fractal::moveViewRight()
{
    _offsetX += VIEW_CHANGE_SIZE / _zoom;
}

void Fractal::changeColor(unsigned char r, unsigned char g, unsigned char b)
{
    _color.r += r;
    _color.g += g;
    _color.b += b;
}
