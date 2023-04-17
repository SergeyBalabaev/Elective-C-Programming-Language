#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

int main()
{
    intdeviceCount;
    cudaDevicePropdevProp;
    cudaGetDeviceCount(&deviceCount);
    printf("Found %d devices\n", deviceCount);

    for (int device = 0; device < deviceCount; device++)
    {
        cudaGetDeviceProperties(&devProp, device);
        printf("Device %d\n", device);
        printf("Compute capability     : %d.%d\n", devProp.major, devProp.minor);
        printf("Name                   : %s\n", devProp.name);
        printf("Total Global Memory    : %u Gb\n", devProp.totalGlobalMem/1024/1024/1024);
        printf("Shared memory per block: %d Kb\n", devProp.sharedMemPerBlock/1024);
        printf("Warp size              : %d\n", devProp.warpSize); //количество нитей в Warp
        printf("Max threads per block  : %d\n", devProp.maxThreadsPerBlock);
    }
    return 0;
}
