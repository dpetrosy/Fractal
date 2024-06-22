#include <cmath>
#include "helpers.hpp"

size_t calcMandelbrot(ComplexNumber& c)
{
	double        reTemp;
	ComplexNumber z;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = reTemp;
	}
	return (i);
}

size_t calcBurningShip(ComplexNumber& c)
{
	double        reTemp;
	ComplexNumber z;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = std::fabs(2.0 * z.re * z.im) + c.im;
		z.re = std::fabs(reTemp);
	}
	return (i);
}

size_t calcTricorn(ComplexNumber& c)
{
	double        reTemp;
	ComplexNumber z;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = -2.0 * z.re * z.im + c.im;
		z.re = reTemp;
	}
	return (i);
}

size_t calcMultibrot(ComplexNumber& c)
{
	ComplexNumber z;
	double reSqr;
	double imSqr;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reSqr = z.re * z.re;
		imSqr = z.im * z.im;
		z.re = z.re * (reSqr*reSqr - 10.0*reSqr*imSqr + 5.0*imSqr*imSqr) + c.re;
		z.im = z.im * (5.0*reSqr*reSqr - 10.0*reSqr*imSqr + imSqr*imSqr) + c.im;
	}
	return (i);
}

size_t calcMandelbar(ComplexNumber& c)
{
	ComplexNumber z;
	double reSqr;
	double imSqr;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reSqr = z.re * z.re;
		imSqr = z.im * z.im;
		z.re = -z.re * (reSqr*reSqr - 10.0*reSqr*imSqr + 5.0*imSqr*imSqr) + c.re;
		z.im = z.im * (5.0*reSqr*reSqr - 10.0*reSqr*imSqr + imSqr*imSqr) + c.im;
	}
	return (i);
}

size_t calcPerBurningShip(ComplexNumber& c)
{
	double        reTemp;
	ComplexNumber z;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * std::fabs(z.im) + c.im;
		z.re = reTemp;
	}
	return (i);
}

size_t calcCelticMandelbrot(ComplexNumber& c)
{
	double        reTemp;
	ComplexNumber z;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = std::fabs(z.re * z.re - z.im * z.im) + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = reTemp;
	}
	return (i);
}