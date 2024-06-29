#include "cuda_utils.cuh"

__device__ size_t calcMandelbrotCUDA(ComplexNumber& c)
{
	ComplexNumber z;
	double reTemp;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = reTemp;
	}
	return (i);
}

__device__ size_t calcJuliaCUDA(ComplexNumber& c)
{
	ComplexNumber z = c;
	double reTemp;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.reJulia;
		z.im = 2.0 * z.re * z.im + c.imJulia;
		z.re = reTemp;
	}
	return (i);
}

__device__ size_t calcBurningShipCUDA(ComplexNumber& c)
{
	ComplexNumber z;
	double reTemp;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = std::fabs(2.0 * z.re * z.im) + c.im;
		z.re = std::fabs(reTemp);
	}
	return (i);
}

__device__ size_t calcTricornCUDA(ComplexNumber& c)
{
	ComplexNumber z;
	double reTemp;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = -2.0 * z.re * z.im + c.im;
		z.re = reTemp;
	}
	return (i);
}

__device__ size_t calcMultibrotCUDA(ComplexNumber& c)
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

__device__ size_t calcMandelbarCUDA(ComplexNumber& c)
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

__device__ size_t calcPerBurningShipCUDA(ComplexNumber& c)
{
	ComplexNumber z;
	double reTemp;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * std::fabs(z.im) + c.im;
		z.re = reTemp;
	}
	return (i);
}

__device__ size_t calcCelticMandelbrotCUDA(ComplexNumber& c)
{
	ComplexNumber z;
	double reTemp;
    size_t i = 0;

	for (; (z.re * z.re + z.im * z.im < 4.0) && i < MAX_ITER; ++i)
	{
		reTemp = std::fabs(z.re * z.re - z.im * z.im) + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = reTemp;
	}
	return (i);
}

__device__ double boxFoldCUDA(double z)
{
	if (z > 1.0)
		z = 2.0 - z;
	else if (z < -1.0)
		z = -2.0 - z;
	return (z);
}

__device__ double ballFoldCUDA(double r, double mag)
{
	if (mag < r)
		mag = mag / (r * r);
	else if (mag < 1.0)
		mag = 1.0 / (mag * mag);
	return (mag);
}

__device__ size_t calcMandelboxCUDA(ComplexNumber& c)
{
	ComplexNumber z = c;
	double mag = 0.0;
    size_t i = 0;

	for (; sqrtf(mag) < 2.0 && i < MAX_ITER; ++i)
	{
		z.re = FIXED_RADIUS * boxFoldCUDA(z.re);
		z.im = FIXED_RADIUS * boxFoldCUDA(z.im);
		mag = sqrtf(z.re * z.re + z.im * z.im);
		z.re = z.re * SCALE * ballFoldCUDA(MINIMUM_RADIUS, mag) + c.re;
		z.im = z.im * SCALE * ballFoldCUDA(MINIMUM_RADIUS, mag) + c.im;
	}
	return (i);
}
