#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include "helpers.hpp"

class Fractal
{
public:
    Fractal();
    ~Fractal();

    Fractal(const Fractal&) = delete;
    Fractal(Fractal&&) = delete;
    Fractal& operator=(const Fractal&) = delete;
    Fractal& operator=(Fractal&&) = delete;

    void reset();
    void colorizePixels(sf::Image& image);
    void setFractalType(std::string type);
    bool isNeedToHandleMouseMoved();

    void zoomIn(int x, int y);
    void zoomOut(int x, int y);

    void moveViewUp();
    void moveViewDown();
    void moveViewLeft();
    void moveViewRight();

    void changeColor(unsigned char r, unsigned char g, unsigned char b);

    void setMouseCoords(int x, int y);

    void switchJuliaLock();

private:
	double      _zoom;
	double      _mouseX;
	double      _mouseY;
	double      _offsetX;
	double      _offsetY;
	RGBColor    _color;
	FractalType _type;
	bool        _isJuliaLocked;
    std::function<size_t(ComplexNumber&)> fractalCallback;
};

#endif  /* FRACTAL_HPP */