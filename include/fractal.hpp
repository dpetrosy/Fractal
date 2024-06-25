#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <functional>
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

    // Zoom event handlers
    void zoomIn(int x, int y);
    void zoomOut(int x, int y);

    // Viewpoint moved event handlers
    void moveViewUp();
    void moveViewDown();
    void moveViewLeft();
    void moveViewRight();

    // Color changed event handlers
    void setColor(unsigned char r, unsigned char g, unsigned char b);
    void changeColor(unsigned char r, unsigned char g, unsigned char b);

    // Julia's fractal events handlers
    void setMouseCoords(int x, int y);
    bool isNeedToHandleMouseMoved();
    void switchJuliaLock();

    typedef std::function<size_t(ComplexNumber&)> CalcCallback;

private:
	double _zoom;
	double _mouseX;
	double _mouseY;
	double _offsetX;
	double _offsetY;
	RGBColor _color;
	FractalType _type;
    ComplexNumber _c;
	bool _isJuliaLocked;
    CalcCallback fractalCallback;
};

#endif  /* FRACTAL_HPP */