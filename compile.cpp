#include <stdio.h>
#include <stdlib.h>

#include "clut.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s kernel-file\n", argv[0]); 
        return 0; 
    }

    int ret; 
    cl_int clErr; 

    cl_platform_id currentPlatform; 
    cl_device_id currentDevice; 
    cl_context context; 

    cl_platform_id *platforms; 
    ret = clGetPlatforms(&platforms); 

    if (!ret) {
        fprintf(stderr, "No avaliable platform. Abort. \n"); 
        return 0; 
    }

    currentPlatform = platforms[0]; 
    printPlatformInfo(currentPlatform); 

    cl_device_id *devices; 
    ret = clGetDevices(currentPlatform, &devices, CL_DEVICE_TYPE_GPU); 

    if (!ret) {
        fprintf(stderr, "No avaliable device. Abort. \n"); 
        return 0; 
    }

    currentDevice = devices[0]; 
    printDeviceInfo(currentDevice);
    clPrintDeviceMemoryInfo(currentDevice); 

    context = clCreateContext(NULL, 1, &currentDevice, NULL, NULL, &clErr); 
    if (clErr != CL_SUCCESS) {
        fprintf(stderr, "Failed to create context. \n"); 
        clperror("Create context", clErr); 
        return 0; 
    }
    
    const char *programSrc = readProgramSource(argv[1], 0x10000); 
    if (!programSrc) {
        return 0; 
    }

    cl_program program = clCreateProgramWithSource(context, 1, &programSrc, NULL, &clErr); 

    if (clErr != CL_SUCCESS) {
        clperror("clCreateProgramWithSource()", clErr); 
        return 0; 
    }

    clErr = clBuildProgram(program, 1, &currentDevice, NULL, NULL, NULL);

    if (clErr == CL_SUCCESS) {
        printf("Compilation Done. \n"); 
    } else {
        clperror("clBuildProgram()", clErr); 
        printf("\n-- Build Log --\n"); 
        clPrintBuildInfo(program, currentDevice); 
    }

    return 0; 
}
