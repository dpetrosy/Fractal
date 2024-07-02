#include "cuda_utils.cuh"
#include "fractal.hpp"

__global__ void computeFractalCUDA(sf::Color* pixels, ComplexNumber c,
    double zoom, double offsetX, double offsetY, RGBColor color, FractalType type)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < WINDOW_SIZE && y < WINDOW_SIZE)
    {
        c.re = x / zoom + offsetX;
        c.im = y / zoom + offsetY;

        size_t iter = 0;
		switch (type)
		{
		case FractalType::Mandelbrot:
			iter = calcMandelbrotCUDA(c);
			break;
		case FractalType::Julia:
			iter = calcJuliaCUDA(c);
			break;
		case FractalType::BurningShip:
			iter = calcBurningShipCUDA(c);
			break;
		case FractalType::Tricorn:
			iter = calcTricornCUDA(c);
			break;
		case FractalType::Mandelbox:
			iter = calcMandelboxCUDA(c);
			break;
		case FractalType::Multibrot:
			iter = calcMultibrotCUDA(c);
			break;
		case FractalType::Mandelbar:
			iter = calcMandelbarCUDA(c);
			break;
		case FractalType::PerBurningShip:
			iter = calcPerBurningShipCUDA(c);
			break;
		case FractalType::CelticMandelbrot:
			iter = calcCelticMandelbrotCUDA(c);
			break;
		default:
			break;
		}

        pixels[y * WINDOW_SIZE + x].r = color.r * iter;
        pixels[y * WINDOW_SIZE + x].g = color.g * iter;
        pixels[y * WINDOW_SIZE + x].b = color.b * iter;
        pixels[y * WINDOW_SIZE + x].a = 255;
    }
}

void colorizePixelsByGPU(sf::Image& image, Fractal& fractal)
{
    sf::Color* imagePtr;
    cudaError_t cudaStatus;
    cudaStatus = cudaMalloc((void**)&imagePtr, WINDOW_SIZE *
        WINDOW_SIZE * sizeof(sf::Color));

    if (cudaStatus != cudaSuccess)
        throw std::runtime_error("-- cudaMalloc error: " +
            std::string(cudaGetErrorString(cudaStatus)));

    // 256 threads per block
    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((WINDOW_SIZE + threadsPerBlock.x - 1) / threadsPerBlock.x,
        (WINDOW_SIZE + threadsPerBlock.y - 1) / threadsPerBlock.y);

    double zoom = fractal.getZoom();
    double offsetX = fractal.getOffsetX();
    double offsetY = fractal.getOffsetY();
    RGBColor& color = fractal.getColor();
    FractalType type = fractal.getType();
    ComplexNumber& c = fractal.getC();

    if (fractal.isNeedToHandleMouseMoved())
    {
        c.reJulia = fractal.getMouseX() / zoom + offsetX;
        c.imJulia = fractal.getMouseY() / zoom + offsetY;
    }

    computeFractalCUDA<<<blocksPerGrid, threadsPerBlock>>>(imagePtr, c, zoom,
        offsetX, offsetY, color, type);
    cudaDeviceSynchronize();

    cudaStatus = cudaMemcpy((void *)image.getPixelsPtr(), imagePtr, WINDOW_SIZE *
        WINDOW_SIZE * sizeof(sf::Color), cudaMemcpyDeviceToHost);

    if (cudaStatus != cudaSuccess)
        throw std::runtime_error("-- cudaMemcpy error: " +
            std::string(cudaGetErrorString(cudaStatus)));
    cudaFree(imagePtr);
}
