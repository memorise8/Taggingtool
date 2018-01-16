// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "../Depends/DefineSensor.h"


// TODO: reference additional headers your program requires here
#ifdef OPENCV
	#include <opencv2\opencv.hpp>
#endif // OPENCV

#include <VTouchSensor.h>
#include "VTouchData.h"

#include "ToolData.h"

#ifdef OPENCV
#ifdef _DEBUG
#pragma comment(lib, "opencv_world320.lib")
#else
#pragma comment(lib, "opencv_world320d.lib")
#endif
#endif
