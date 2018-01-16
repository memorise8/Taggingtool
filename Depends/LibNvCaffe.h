#pragma once

// Use TensorRT in Linux
#include "NvInfer.h"
#include "NvCaffeParser.h"

#include <cuda_runtime_api.h>

using namespace nvinfer1;
using namespace nvcaffeparser1;

#ifndef CUDA_CHECK
#define CUDA_CHECK(status)									\
{														\
	if (status != 0)									\
	{													\
		std::cout << "Cuda failure: " << status;		\
		abort();										\
	}													\
}
#endif


void createMemory(const ICudaEngine& engine, void** buffer, const std::string& name);
ICudaEngine* createEngine(std::string deployFile, std::string modelFile, std::string output_blob_name);
ICudaEngine* createEngineFromGIE(std::string gieFile);