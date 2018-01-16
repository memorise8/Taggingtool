// TaggingTools.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Core.h"
#include "FileManager.h"
#include "DataProcess.h"

void Read()
{
	FileManager fm("D:/daa/");
	fm.Read(1);
}

void Write()
{
	const char* strStoreFileDir = "";
	FileManager fm(strStoreFileDir);
	fm.Write();
}

void GetFileData()
{

}

void SetData()
{
	DataProcess data;

	data.SetData();
}

void convertDataFromVideo()
{
	vt::Core core;

	vt::VTouchData::getInstance()->sensorType = SENSOR_KINECT_V2;
	
	if(vt::VTouchData::getInstance()->sensorType == -1)
	{
		std::cout << "There is no define sensor type" << std::endl;
		return;
	}
	else if(vt::VTouchData::getInstance()->sensorType == SENSOR_KINECT_V2)
	{
		if(core.Initialize() < 0)
		{
			printf("initialize failed\n");
		}
		else
		{
			core.Run();
		}
	}
	else if(vt::VTouchData::getInstance()->sensorType == SENSOR_PMD)
	{

	}
	else if(vt::VTouchData::getInstance()->sensorType == SENSOR_MEERAE)
	{

	}
}

int main()
{
	while (1)
	{
		
		convertDataFromVideo();

	}
    return 0;
}

