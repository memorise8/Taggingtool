#include "stdafx.h"
#include "DataProcess.h"

void DataProcess::OnClickWindow(int event, int x, int y, int flags, void * userdata)
{

	DataProcess* v = (DataProcess*)userdata;

	bool draw = false;

	switch (event)
	{
	default:
		break;
	case cv::EVENT_LBUTTONDOWN:
	{
		if (flags & cv::EVENT_FLAG_SHIFTKEY)
		{
			int a = 0;
		}
		else
		{

			v->startPoint = cv::Point(x, y);
			v->setPoints.push_back(v->startPoint);

		}
		
	}
	break;

	case cv::EVENT_LBUTTONUP:
	{
		if (flags & cv::EVENT_FLAG_SHIFTKEY)
		{
			int a = 0;
		}
		else 
		{
			v->endPoint = cv::Point(x, y);
			cv::Rect drawRectangle = cv::Rect(v->startPoint, v->endPoint);
			v->setRects.push_back(drawRectangle);
			v->startPoint = cv::Point(0, 0);
			v->endPoint = cv::Point(0, 0);
			draw = false;
		}
		
	}
	break;

	case cv::EVENT_MOUSEMOVE:
	{
		if (v->startPoint.x > 0)
		{
			cv::Mat tempShowMat = v->makeDataMat.clone();
			cv::rectangle(tempShowMat, cv::Rect(v->startPoint, cv::Point(x,y)), cv::Scalar(0, 0, 255), 1);
			cv::imshow("test", tempShowMat);
		}
	}
	break;
	}

}


DataProcess::DataProcess()
{
	dat = ToolData::getInstance();
}


DataProcess::~DataProcess()
{
}

void DataProcess::GetData()
{

}

void DataProcess::SetData()
{
	this->makeData(2);
	dat->vecPoint = this->setPoints;
	dat->vecRect = this->setRects;
	this->setRects.clear();
	this->setPoints.clear();
}

void DataProcess::drawRect(cv::Rect &rt)
{
	rt = drawRect();
}

void DataProcess::drawPoint(cv::Point &pt)
{
	pt = drawPoint();
}

cv::Rect DataProcess::drawRect()
{
	cv::Rect rt = cv::Rect(-1, -1, 0, 0);

	for (;;)
	{
		if (rt.x == -1)
		{
			if (this->setRects.size() > 0)
				for (int i = 0; i < this->setRects.size(); ++i)
					cv::rectangle(makeDataMat, this->setRects[i], cv::Scalar(0, 0, 255), 1);
			cv::imshow("test", makeDataMat);
			cv::setMouseCallback("test", OnClickWindow, this);
			int key = cv::waitKey(1);
			if (key == 'c')
				break;
		}

	}

	return rt;
}

cv::Point DataProcess::drawPoint()
{
	cv::Point pt = cv::Point(0, 0);

	for (;;)
	{
		if (pt.x == 0) // no input data
		{
			if (this->setPoints.size() > 0)
				for (int i = 0; i < this->setPoints.size(); ++i)
					cv::circle(makeDataMat, this->setPoints[i], 1, cv::Scalar(255, 255, 255), 1);
			cv::imshow("test", makeDataMat);
			cv::setMouseCallback("test", OnClickWindow, this);
			int key = cv::waitKey(1);
			if (key == 'c')
				break;
		}
	}
	

	return pt;
}

void DataProcess::makeData(int flag)
{
	cv::Mat tempMat;
	tempMat = dat->setData().clone();
	
	tempMat = cv::Mat(424, 512, CV_8UC3);

	makeDataMat = tempMat.clone();

	switch (flag)
	{
	default:
		break;

	case 1:
		drawPoint();
		break;
	case 2:
		drawRect();
		break;
	}

	makeDataMat = cv::Mat();
}

