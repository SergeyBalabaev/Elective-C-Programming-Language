#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include "stdio.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <cuda.h>
#include <ctime>
#include <assert.h>
#include <math.h>
#include <cmath>

#include "helper_image.h"

typedef unsigned char  uchar;
typedef unsigned int  uint;

texture<unsigned char, 2, cudaReadModeElementType> g_Texture;

unsigned int width = 512, height = 512;
template<class T, enum cudaTextureReadMode readMode>
T tex2D(texture<T, 2, readMode> texRef, float x, float y);// <тип, размерность>


__global__ 
void negative_kernel(unsigned char* dest, int width, int height)
{
int tidx = threadIdx.x + blockIdx.x * blockDim.x;
int tidy = threadIdx.y + blockIdx.y * blockDim.y;

// проверка, что текущие индексы не выходят за границы изображения
if (tidx < width && tidy < height)
{
unsigned char c = tex2D(g_Texture, tidx + 0.5f, tidy + 0.5f);
// преобразование для негатива
//unsigned char r = 255 - c;
dest[tidx + tidy * width] = 255 - c; //r;

}
}
__global__
void GaussianK(uchar* pDst, int radius, float radius2, uint w, uint h)
{
int tidx = threadIdx.x + blockIdx.x * blockDim.x;
int tidy = threadIdx.y + blockIdx.y * blockDim.y;
// проверка, что текущие индексы не выходят за границы изображения
if (tidx < w && tidy < h)
{
float r = 0;
float weight_sum = 0.0f;
float weight = 0.0f;
for (int ic = -radius; ic <= radius; ic++)
{
weight = (float)exp(-(ic * ic) / (radius2 * radius2)) / (radius2 * 2.5);
r += tex2D(g_Texture, tidx + 0.5f + ic, tidy + 0.5f) * weight;
weight_sum += weight;
}
//нормализация полученных результатов
r /= weight_sum;
pDst[tidx + tidy * w] = (uchar)r;
}
}
void loadImage(char* file, unsigned char** pixels, unsigned int* width, unsigned int* height)
{
size_t file_length = strlen(file);
if (!strcmp(&file[file_length - 3], "pgm"))
{
if (sdkLoadPGM<unsigned char>(file, pixels, width, height) != true)
{
printf("Failed to load PGM image file: %s\n", file);
exit(EXIT_FAILURE);
}
}
return;
}
void saveImage(char* file, unsigned char* pixels, unsigned int width, unsigned int height)
{
size_t file_length = strlen(file);
if (!strcmp(&file[file_length - 3], "pgm"))
{
sdkSavePGM(file, pixels, width, height);
}
return;
}
int main(int argc, char** argv)
{

unsigned char* d_result_pixels;
unsigned char* h_result_pixels;
unsigned char* h_pixels = NULL;
unsigned char* d_pixels = NULL;
char* src_path = "Lenna.pgm";
char* d_result_path = "Lenna_s.pgm";
loadImage(src_path, &h_pixels, &width, &height);
int image_size = sizeof(unsigned char) * width * height;
h_result_pixels = (unsigned char*)malloc(image_size);
cudaMalloc((void**)&d_pixels, image_size);
cudaMalloc((void**)&d_result_pixels, image_size);
cudaMemcpy(d_pixels, h_pixels, image_size, cudaMemcpyHostToDevice);
int n = 16;
dim3 block(n, n);
dim3 grid(width / n, height / n);
cudaChannelFormatDesc desc = cudaCreateChannelDesc<uchar1>();
size_t offset = 0;
cudaError_t error = cudaBindTexture2D(0, &g_Texture, d_pixels, &desc, width, height, width * sizeof(unsigned char));
if (cudaSuccess != error) {
printf("ERROR: Failed to bind texture.\n");
exit(-1);
}
else {
printf("Texture was successfully binded\n");
}
negative_kernel << < grid, block >> > (d_result_pixels, width, height);
//GaussianK << < grid, block >> > (d_result_pixels, 10, 10, width, height);
cudaMemcpy(h_result_pixels, d_result_pixels, image_size, cudaMemcpyDeviceToHost);
saveImage(d_result_path, h_result_pixels, width, height);
cudaUnbindTexture(&g_Texture);

return 0;
}
