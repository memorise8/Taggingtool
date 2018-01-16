#include "stdafx.h"
#include "ToolData.h"

ToolData* ToolData::instance;

ToolData::ToolData()
{
	vtouch = vt::VTouchData::getInstance();
}


ToolData::~ToolData()
{
}


cv::Mat ToolData::setData()
{
	return cv::Mat();
}