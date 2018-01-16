//////////////////////////////////////////////////////////////////////////
// Common settings
//#pragma warning(disable : 4819 )
//#pragma warning(disable : 4996 )

//////////////////////////////////////////////////////////////////////////
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/ml/ml.hpp>


//#define USE_OPENCV_249
//#define USE_OPENCV_2413
//#define USE_WINCAFFE_OPENCV // a variant of opencv 310

#ifdef USE_OPENCV_249
#ifdef _DEBUG
#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")
#pragma comment(lib, "opencv_ml249d.lib")
#pragma comment(lib, "opencv_video249d.lib")
#else
#pragma comment(lib, "opencv_core249.lib")
#pragma comment(lib, "opencv_highgui249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_ml249.lib")
#pragma comment(lib, "opencv_video249.lib")
#endif
#endif

#ifdef USE_OPENCV_2410
#ifdef _DEBUG
#pragma comment(lib, "opencv_core2410d.lib")
#pragma comment(lib, "opencv_highgui2410d.lib")
#pragma comment(lib, "opencv_imgproc2410d.lib")
#pragma comment(lib, "opencv_ml2410d.lib")
#pragma comment(lib, "opencv_video2410d.lib")
#else
#pragma comment(lib, "opencv_core2410.lib")
#pragma comment(lib, "opencv_highgui2410.lib")
#pragma comment(lib, "opencv_imgproc2410.lib")
#pragma comment(lib, "opencv_ml2410.lib")
#pragma comment(lib, "opencv_video2410.lib")
#endif
#endif

#ifdef USE_OPENCV_2413
#ifdef _DEBUG
#pragma comment(lib, "opencv_core2413d.lib")
#pragma comment(lib, "opencv_highgui2413d.lib")
#pragma comment(lib, "opencv_imgproc2413d.lib")
#pragma comment(lib, "opencv_ml2413d.lib")
#pragma comment(lib, "opencv_video2413d.lib")
#else
#pragma comment(lib, "opencv_core2413.lib")
#pragma comment(lib, "opencv_highgui2413.lib")
#pragma comment(lib, "opencv_imgproc2413.lib")
#pragma comment(lib, "opencv_ml2413.lib")
#pragma comment(lib, "opencv_video2413.lib")
#endif
#endif

#ifdef USE_WINCAFFE_OPENCV
#ifdef _DEBUG
//#pragma comment(lib, "proto-d.lib")
//#pragma comment(lib, "libprotobufd.lib")
//#pragma comment(lib, "libboost_chrono-vc140-mt-1_61.lib")
//#pragma comment(lib, "libboost_filesystem-vc140-mt-gd-1_61.lib")
//#pragma comment(lib, "libboost_system-vc140-mt-gd-1_61.lib")
//#pragma comment(lib, "libboost_filesystem-vc140-mt-gd-1_61.lib")
//#pragma comment(lib, "libboost_thread-vc140-mt-gd-1_61.lib")
//#pragma comment(lib, "caffehdf5_D.lib")
//#pragma comment(lib, "caffehdf5_hl_D.lib")
//#pragma comment(lib, "gflagsd.lib")
//#pragma comment(lib, "glogd.lib")
//#pragma comment(lib, "libopenblas.lib"
//#pragma comment(lib, "opencv_core310d.lib")
//#pragma comment(lib, "opencv_imgcodecs310d.lib")
//#pragma comment(lib, "opencv_imgproc310d.lib")
//#pragma comment(lib, "opencv_highgui310d.lib")
//#pragma comment(lib, "leveldbd.lib")
//#pragma comment(lib, "lmdbd.lib")
//#pragma comment(lib, "caffe-d.lib")
//#pragma comment(lib, "ntdll.lib")

#else
#pragma comment(lib, "opencv_world310.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////
// Namespaces
using namespace cv;