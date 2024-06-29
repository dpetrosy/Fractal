#ifndef CUDA_UTILS_CUH
#define CUDA_UTILS_CUH

#include <SFML/Graphics.hpp>
#include <cuda_runtime.h>
#include "helpers.hpp"

__device__ size_t calcMandelbrotCUDA(ComplexNumber& c);
__device__ size_t calcJuliaCUDA(ComplexNumber& c);
__device__ size_t calcBurningShipCUDA(ComplexNumber& c);
__device__ size_t calcTricornCUDA(ComplexNumber& c);
__device__ size_t calcMandelboxCUDA(ComplexNumber& c);
__device__ size_t calcMultibrotCUDA(ComplexNumber& c);
__device__ size_t calcMandelbarCUDA(ComplexNumber& c);
__device__ size_t calcPerBurningShipCUDA(ComplexNumber& c);
__device__ size_t calcCelticMandelbrotCUDA(ComplexNumber& c);

#endif  /* CUDA_UTILS_CUH */