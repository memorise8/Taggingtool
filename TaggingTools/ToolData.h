#pragma once

class ToolData
{
public:
	
	inline static ToolData* getInstance()
	{
		if (instance == 0) instance = new ToolData();

		return instance;
	}

	~ToolData();

	cv::Mat setData();

	std::vector<cv::Point> vecPoint;
	std::vector<cv::Rect> vecRect;
	
	vt::VTouchData* vtouch;

private:
	ToolData();
	static ToolData *instance;
};

