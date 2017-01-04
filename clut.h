//
//  clut.h
//  PAD
//
//  Created by Jimmy Sinn on 6/2/15.
//  Copyright (c) 2015 Jimmy Sinn. All rights reserved.
//

#ifndef __PAD__clut__
#define __PAD__clut__

#include <cstdio>
#include <cstring>

#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/cl.h>
#endif

#if defined(__linux__)
#define printe(fmt, arg ...) \
do { \
time_t rawtime; \
time(&rawtime); \
char *tmp = ctime(&rawtime); \
tmp[strlen(tmp) - 1] = 0; \
fprintf(stderr, "[0;43;30m[%s][0m [1;33m[%s: %10s(): %3d][0m " fmt "\n", \
tmp , __FILE__, __FUNCTION__, __LINE__, ##arg); \
} while (0)
#elif defined(__APPLE__)
#define printe(fmt, arg ...) \
do { \
time_t rawtime; \
time(&rawtime); \
char *tmp = ctime(&rawtime); \
tmp[strlen(tmp) - 1] = 0; \
fprintf(stderr, "[%s] [%s: %10s(): %3d] " fmt "\n", \
tmp , __FILE__, __FUNCTION__, __LINE__, ##arg); \
} while (0)
#else
#define printe printf
#endif

#define clperror(str, err)           \
if (err != CL_SUCCESS) {\
printe("%s: %s\n", str, clErrorString(err)); \
throw -1; \
}
//getchar();

const char* clErrorString(cl_int err);
void printPlatformInfo(cl_platform_id id);
void printDeviceInfo(cl_device_id device);

int clGetPlatforms(cl_platform_id **out = NULL, bool print = false);
int clGetDevices(cl_platform_id platform, cl_device_id **out, cl_device_type type = CL_DEVICE_TYPE_ALL);

int clGetDeviceNum(int platformId, cl_device_type type = CL_DEVICE_TYPE_GPU);

char *readProgramSource(const char *filename, int maxSize = 0x10000);

void printMachineConfig();
void clPrintBuildInfo(cl_program program, cl_device_id device);
void clPrintDeviceMemoryInfo(cl_device_id device);

cl_program clCompileProgramFromSource(cl_context context, cl_device_id device, const char *src);
cl_program clCompileProgramFromFile(cl_context context, cl_device_id device, const char *filename);


#endif /* defined(__PAD__clut__) */
