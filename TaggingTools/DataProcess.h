#pragma once
class DataProcess
{
public:
	DataProcess();
	~DataProcess();

	void GetData();
	void SetData();

	ToolData* dat;

private:
#ifdef OPENCV
	cv::Mat input;
	cv::Mat output;

	static void OnClickWindow(int event, int x, int y, int flags, void* userdata);
#endif // OPENCV

	void makeData(int flag);
	
	void drawRect(cv::Rect &rt);
	void drawPoint(cv::Point &pt);

	cv::Rect drawRect();
	cv::Point drawPoint();

	cv::Point startPoint;
	cv::Point endPoint;

	std::vector<cv::Point> setPoints;
	std::vector<cv::Rect> setRects;

	cv::Mat makeDataMat;

};

