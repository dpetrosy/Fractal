#include "fractal.hpp"

Fractal::Fractal()
{
    reset();
    setColor(RED, GREEN, BLUE);
    setFractalType(MandelbrotStr);
}

Fractal::~Fractal()
{}

void Fractal::reset()
{
    _mouseX = 0;
    _mouseY = 0;
    _offsetX = -2;
    _offsetY = -2;
    _zoom = WINDOW_SIZE / 4;
    _isJuliaLocked = false;
}

void Fractal::colorizePixels(sf::Image& image)
{
    size_t iterCount;
	static ComplexNumber c;

    for (int i = 0; i < WINDOW_SIZE; ++i)
    {
        c.re = i / _zoom + _offsetX;
        if (_type == FractalType::Julia && !_isJuliaLocked)
            c.reJulia = _mouseX / _zoom + _offsetX;
        for (int j = 0; j < WINDOW_SIZE; ++j)
        {
            c.im = j / _zoom + _offsetY;
            if (_type == FractalType::Julia && !_isJuliaLocked)
                c.imJulia = _mouseY / _zoom + _offsetY;
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
        fractalCallback = calcJulia;
    }
    else if (type == BurningShipStr)
    {
        _type = FractalType::BurningShip;
        fractalCallback = calcBurningShip;
    }
    else if (type == TricornStr)
    {
        _type = FractalType::Tricorn;
        fractalCallback = calcTricorn;
    }
    else if (type == MandelboxStr)
    {
        _type = FractalType::Mandelbox;
        fractalCallback = calcMandelbox;
    }
    else if (type == MultibrotStr)
    {
        _type = FractalType::Multibrot;
        fractalCallback = calcMultibrot;
    }
    else if (type == MandelbarStr)
    {
        _type = FractalType::Mandelbar;
        fractalCallback = calcMandelbar;
    }
    else if (type == PerBurningShipStr)
    {
        _type = FractalType::PerBurningShip;
        fractalCallback = calcPerBurningShip;
    }
    else if (type == CelticMandelbrotStr)
    {
        _type = FractalType::CelticMandelbrot;
        fractalCallback = calcCelticMandelbrot;
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

void Fractal::setColor(unsigned char r, unsigned char g, unsigned char b)
{
    _color.r = r;
    _color.g = g;
    _color.b = b;
}

void Fractal::changeColor(unsigned char r, unsigned char g, unsigned char b)
{
    _color.r += r;
    _color.g += g;
    _color.b += b;
}

void Fractal::setMouseCoords(int x, int y)
{
    if (isNeedToHandleMouseMoved())
    {
        _mouseX = x;
        _mouseY = y;
    }
}

bool Fractal::isNeedToHandleMouseMoved()
{
    return (_type == FractalType::Julia && !_isJuliaLocked);
}

void Fractal::switchJuliaLock()
{
    _isJuliaLocked = !_isJuliaLocked;
}