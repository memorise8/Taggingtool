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
	FileManager fm("");
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

	if(SENSOR_TYPE == SENSOR_UNKNOWN)
	{
		std::cout << "There is no define sensor type" << std::endl;
		return;
	}
	else if(SENSOR_TYPE == SENSOR_KINECT_V2)
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
	else if(SENSOR_TYPE == SENSOR_PMD)
	{

	}
	else if(SENSOR_TYPE == SENSOR_MEERAE)
	{

	}
};

}

int main()
{
	Read();

	SetData();

    return 0;
}

