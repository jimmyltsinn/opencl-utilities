//
//  clut.cpp
//  PAD
//
//  Created by Jimmy Sinn on 6/2/15.
//  Copyright (c) 2015 Jimmy Sinn. All rights reserved.
//

#include <iostream>

#include "clut.h"

using namespace std;

const char* clErrorString(cl_int err) {
    switch (err) {
        case CL_SUCCESS:                            return "Success";
        case CL_DEVICE_NOT_FOUND:                   return "Device not found";
        case CL_DEVICE_NOT_AVAILABLE:               return "Device not available";
        case CL_COMPILER_NOT_AVAILABLE:             return "Compiler not available";
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:      return "Memory object allocation failure";
        case CL_OUT_OF_RESOURCES:                   return "Out of resources";
        case CL_OUT_OF_HOST_MEMORY:                 return "Out of host memory";
        case CL_PROFILING_INFO_NOT_AVAILABLE:       return "Profiling info not available";
        case CL_MEM_COPY_OVERLAP:                   return "Memory copy overlap";
        case CL_IMAGE_FORMAT_MISMATCH:              return "Image format mismatch";
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:         return "Image format not supported";
        case CL_BUILD_PROGRAM_FAILURE:              return "Build program failure";
        case CL_MAP_FAILURE:                        return "Map failure";
        case CL_INVALID_VALUE:                      return "Invalid value";
        case CL_INVALID_DEVICE_TYPE:                return "Invalid device type";
        case CL_INVALID_PLATFORM:                   return "Invalid platform";
        case CL_INVALID_DEVICE:                     return "Invalid device";
        case CL_INVALID_CONTEXT:                    return "Invalid context";
        case CL_INVALID_QUEUE_PROPERTIES:           return "Invalid queue properties";
        case CL_INVALID_COMMAND_QUEUE:              return "Invalid command queue";
        case CL_INVALID_HOST_PTR:                   return "Invalid host pointer";
        case CL_INVALID_MEM_OBJECT:                 return "Invalid memory object";
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:    return "Invalid image format descriptor";
        case CL_INVALID_IMAGE_SIZE:                 return "Invalid image size";
        case CL_INVALID_SAMPLER:                    return "Invalid sampler";
        case CL_INVALID_BINARY:                     return "Invalid binary";
        case CL_INVALID_BUILD_OPTIONS:              return "Invalid build options";
        case CL_INVALID_PROGRAM:                    return "Invalid program";
        case CL_INVALID_PROGRAM_EXECUTABLE:         return "Invalid program executable";
        case CL_INVALID_KERNEL_NAME:                return "Invalid kernel name";
        case CL_INVALID_KERNEL_DEFINITION:          return "Invalid kernel definition";
        case CL_INVALID_KERNEL:                     return "Invalid kernel";
        case CL_INVALID_ARG_INDEX:                  return "Invalid argument index";
        case CL_INVALID_ARG_VALUE:                  return "Invalid argument value";
        case CL_INVALID_ARG_SIZE:                   return "Invalid argument size";
        case CL_INVALID_KERNEL_ARGS:                return "Invalid kernel arguments";
        case CL_INVALID_WORK_DIMENSION:             return "Invalid work dimension";
        case CL_INVALID_WORK_GROUP_SIZE:            return "Invalid work group size";
        case CL_INVALID_WORK_ITEM_SIZE:             return "Invalid work item size";
        case CL_INVALID_GLOBAL_OFFSET:              return "Invalid global offset";
        case CL_INVALID_EVENT_WAIT_LIST:            return "Invalid event wait list";
        case CL_INVALID_EVENT:                      return "Invalid event";
        case CL_INVALID_OPERATION:                  return "Invalid operation";
        case CL_INVALID_GL_OBJECT:                  return "Invalid OpenGL object";
        case CL_INVALID_BUFFER_SIZE:                return "Invalid buffer size";
        case CL_INVALID_MIP_LEVEL:                  return "Invalid MIP level";
        case CL_INVALID_GLOBAL_WORK_SIZE:           return "Invalid global work size";
        default:                                    return "Unknown error";
    }
}

void __clperror(const char *str, cl_int err) {
    // if (err != CL_SUCCESS)
    cerr << str << ": " << clErrorString(err) << "\n";
}

void printPlatformInfo(cl_platform_id id) {
    cl_platform_info platformInfoList[] = {
        CL_PLATFORM_NAME,
        CL_PLATFORM_PROFILE,
        CL_PLATFORM_VERSION,
        CL_PLATFORM_VENDOR,
        CL_PLATFORM_EXTENSIONS
    };
    
    const char str[][50] = {
        "Platform: ",
        "\tPlatform Profile",
        "\tOpenCL Version",
        "\tVendor",
        "\tExtension"
    };
    cl_int err;
    size_t currentSize = 100;
    char *tmp = (char *) malloc(currentSize * sizeof(char));
    
    for (int i = 0; i < 5; ++i) {
        size_t s;
        err = clGetPlatformInfo(id, platformInfoList[i], 0, NULL, &s);
        if (err) {
            clperror("clGetPlatformInfo()", err);
            return;
        }
        if (s > currentSize) {
            currentSize = s;
            free(tmp);
            tmp = (char *) malloc(currentSize * sizeof(char));
        }
        err = clGetPlatformInfo(id, platformInfoList[i], currentSize, tmp, NULL);
        
        if (err) {
            clperror("clGetPlatformInfo()", err);
            return;
        }
        
        cout << str[i] << '\t' << tmp << '\n';
        
    }
    free(tmp);
    
}

void printDeviceInfo(cl_device_id device) {
    char buf[1024];
    int i;
    size_t s;
    cl_int err;
    cl_device_type t;
    
    err = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(buf), &buf, NULL);
    cout << buf << '\n';
    
    buf[0] = 0;
    
    err = clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(t), &t, NULL);
    clperror("clGetDeviceInfo", err);
    
    cout << "\tCL_DEVICE_TYPE: ";
    
    if (t & CL_DEVICE_TYPE_DEFAULT)     cout << "Default ";
    if (t & CL_DEVICE_TYPE_CPU)         cout << "CPU ";
    if (t & CL_DEVICE_TYPE_GPU)         cout << "GPU ";
    if (t & CL_DEVICE_TYPE_ACCELERATOR) cout << "Accelerator ";
#ifdef __APPLE__
    if (t & CL_DEVICE_TYPE_CUSTOM)      cout << "Custom ";
#endif
    
    cout << '\n';
    
    err = clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(buf), &buf, NULL);
    cout << "\tCL_DEVICE_VENDOR: " << buf << '\n';
    
    err = clGetDeviceInfo(device, CL_DRIVER_VERSION, sizeof(buf), &buf, NULL);
    cout << "\tCL_DRIVER_VERSION: " << buf << '\n';
    
    err = clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(buf), &buf, NULL);
    cout << "\tCL_DEVICE_VERSION: " << buf << '\n';
    
    err = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(i), &i, NULL);
    cout << "\tCL_DEVICE_MAX_COMPUTE_UNIT: " << i << '\n';
    
    err = clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(i), &i, NULL);
    cout << "\tCL_DEVICE_MAX_CLOCK_FREQUENCY: " << i << '\n';
    
    err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(s), &s, NULL);
    cout << "\tCL_DEVICE_MAX_WORK_GROUP_SIZE: " << s << '\n';
    
    //    err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(i), &i, NULL);
    //    cout << "\tCL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: " << i << '\n';
}

int clGetPlatforms(cl_platform_id **out, bool print) {
    int ret;
    cl_uint ret2;
    cl_int err;
    
    err = clGetPlatformIDs(0, NULL, &ret2);
    ret = ret2;
    
    if (err) {
        clperror("clGetPlatformIds()", err);
        return 0;
    }
    
    if (!ret)
        return 0;
    
    if (out || print) {
        cl_platform_id *platformIds;
        
        platformIds = (cl_platform_id *) malloc(ret * sizeof(cl_platform_id));
        err = clGetPlatformIDs(ret, platformIds, NULL);
        
        if (print) {
            for (int i = 0; i < ret; ++i) {
                printPlatformInfo(platformIds[i]);
            }
            
        }
        
        if (out)
            *out = platformIds;
        else
            free(platformIds);
    }
    
    return ret;
}

int clGetDevices(cl_platform_id platform, cl_device_id **out, cl_device_type type) {
    cl_uint ret2;
    cl_int err;
    
    int ret;
    
    err = clGetDeviceIDs(platform, type, 0, NULL, &ret2);
    clperror("clGetDeviceIDs", err);
    
    ret = ret2;
    
    *out = (cl_device_id *) malloc(sizeof(cl_device_id) * ret);
    clGetDeviceIDs(platform, type, ret, *out, NULL);
    clperror("clGetDeviceIDs", err);
    
    return ret;
}

const char *readProgramSource(const char *filename, int maxSize) {
    FILE *fp = fopen(filename, "r");
    
    if (!fp) {
        perror("Open kernel file");
        return NULL;
    }
    
    char *ret = (char *) malloc(maxSize * sizeof(char));
    size_t len = fread(ret, 1, maxSize, fp);
    ret[len] = 0;
    
    fclose(fp);
    return ret;
}

void printMachineConfig() {
    cl_platform_id *platforms;
    
    int platformNum = clGetPlatforms(&platforms, false);
    
    for (int i = 0; i < platformNum; ++i) {
        int deviceNum;
        cl_device_id *devices;
        printPlatformInfo(platforms[i]);
        deviceNum = clGetDevices(platforms[i], &devices);
        for (int j = 0; j < deviceNum; ++j)
            printDeviceInfo(devices[j]);
        free(devices);
    }
    
    free(platforms);
}

void clPrintBuildInfo(cl_program program, cl_device_id device) {
    int size = 4096;
    cl_int clErr = 0;
    do {
        size <<= 1;
        size_t length;
        char *buffer = (char *) malloc(sizeof(char) * size);
        clErr = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, size, buffer, &length);
        if (!clErr)
            cerr << buffer << '\n';
        free(buffer);
    } while (clErr);
}

void clPrintDeviceMemoryInfo(cl_device_id device) {
    cl_ulong val;
    clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(val), &val, NULL);
    std::cout << "Global Memory: " << val / 1024 / 1024 << " MB\n";
    clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(val), &val, NULL);
    std::cout << "Local Memory: " << val / 1024 << " KB\n";
    clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(val), &val, NULL);
    std::cout << "Constant Memory: " << val / 1024 << " KB\n";
}
