//
//  clut.h
//  PAD
//
//  Created by Jimmy Sinn on 6/2/15.
//  Copyright (c) 2015 Jimmy Sinn. All rights reserved.
//

#ifndef __PAD__clut__
#define __PAD__clut__

#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/cl.h>
#endif

//#ifndef _WIN32
//#define printe(fmt, arg ...) \
//do { \
//time_t rawtime; \
//time(&rawtime); \
//char *tmp = ctime(&rawtime); \
//tmp[strlen(tmp) - 1] = 0; \
//fprintf(stderr, "[0;43;30m[%s][0m [1;33m[%s: %10s(): %3d][0m " fmt "\n", \
//tmp , __FILE__, __FUNCTION__, __LINE__, ##arg); \
//} while (0)
//#else
//#define printe printf
//#endif

#define clperror(str, err)           \
    if (err != CL_SUCCESS) \
    fprintf(stderr, "%s: %s\n", str, clErrorString(err))

const char* clErrorString(cl_int err);
void printPlatformInfo(cl_platform_id id);
void printDeviceInfo(cl_device_id device);

int clGetPlatforms(cl_platform_id **out = NULL, bool print = false);
int clGetDevices(cl_platform_id platform, cl_device_id **out, cl_device_type type = CL_DEVICE_TYPE_ALL);

const char *readProgramSource(const char *filename, int maxSize = 1024);

void printMachineConfig();
void clPrintBuildInfo(cl_program program, cl_device_id device);
void clPrintDeviceMemoryInfo(cl_device_id device);

#endif /* defined(__PAD__clut__) */
