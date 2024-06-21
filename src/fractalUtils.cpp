#include <cmath>
#include "fractalUtils.hpp"

size_t calcMandelbrot(ComplexNumber& c)
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

size_t calcBurningShip(ComplexNumber& c)
{
	double        reTemp;
	ComplexNumber z;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = fabs(2 * z.re * z.im) + c.im;
		z.re = fabs(reTemp);
	}
	return (i);
}

size_t calcMultibrot(ComplexNumber& c)
{
	ComplexNumber z;
	double reSqr;
	double imSqr;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4) && i < MAX_ITER; ++i)
	{
		reSqr = z.re * z.re;
		imSqr = z.im * z.im;
		z.re = z.re * (reSqr*reSqr - 10*reSqr*imSqr + 5*imSqr*imSqr) + c.re;
		z.im = z.im * (5*reSqr*reSqr - 10*reSqr*imSqr + imSqr*imSqr) + c.im;
	}
	return (i);
}

size_t calcMandelbar(ComplexNumber& c)
{
	ComplexNumber z;
	double reSqr;
	double imSqr;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4) && i < MAX_ITER; ++i)
	{
		reSqr = z.re * z.re;
		imSqr = z.im * z.im;
		z.re = -z.re * (reSqr*reSqr - 10*reSqr*imSqr + 5*imSqr*imSqr) + c.re;
		z.im = z.im * (5*reSqr*reSqr - 10*reSqr*imSqr + imSqr*imSqr) + c.im;
	}
	return (i);
}