#pragma once

#include "caffe/caffe.hpp"
#include "caffe/util/io.hpp"
#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/filler.hpp"

using namespace caffe;
typedef double Dtype;

#ifndef CPU_ONLY
#pragma comment(lib, "cudnn.lib")
#pragma comment(lib, "curand.lib")
#pragma comment(lib, "cuda.lib")
#pragma comment(lib, "cudart.lib")
#pragma comment(lib, "cublas.lib")
#endif