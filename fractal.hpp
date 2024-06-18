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

    double getZoom();
    double getOffsetX();
    double getOffsetY();
    u_int32_t getColor();

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

#endif  /* FRACTAL_HPP */