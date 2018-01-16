#include "stdafx.h"
#include "Core.h"

namespace vt {

	Core::Core()
		:vtouch(NULL)
		, is_running(false)
	{
	}

	Core::~Core()
	{
	}

	int Core::GetSensorData()
	{

		// Depth image
		int hr = vtouch->sensor->AccessDepthFrameBuffer(vtouch->depthHeight * vtouch->depthWidth * sizeof(ushort), &vtouch->m_depthMat.data);

		if (hr >= 0)
		{
			hr = vtouch->mapper->MapDepthFrameToWorldSpace(vtouch->m_depthMat.total(), vtouch->m_depthMat.data, vtouch->m_worldMat.data);
		}

		// IR image
		if (hr >= 0)
		{
			hr = vtouch->sensor->AccessInfraredFrameBuffer(vtouch->depthHeight * vtouch->depthWidth, &vtouch->m_infraredMat.data);
		}

		// confidence value
		if (vtouch->sensorType == SENSOR_PMD)
		{
			if (hr >= 0)
			{
				hr = vtouch->sensor->AccessDepthConfidenceBuffer(vtouch->depthHeight * vtouch->depthWidth, &vtouch->m_confidenceMat.data);
			}
		}

		// Color image if avaiable
		if (vtouch->sensorType == SENSOR_KINECT_V2)
		{
			if (hr >= 0)
			{
				bool h = vtouch->sensor->GetColorFrame(vtouch->colorHeight * vtouch->colorWidth, vtouch->m_grayMat.data);

				/*if (h)
				{
				vtouch->color_skipped = false;
				}
				else
				{
				vtouch->color_skipped = true;
				}*/

				hr = vtouch->mapper->MapColorFrameToWorldSpace(vtouch->depthHeight * vtouch->depthWidth, vtouch->m_depthMat.data);
			}

			/*	if (hr >= 0)
			{
			hr = vtouch->sensor->GetBodyData(vtouch->skeletonData);
			}*/

			if (hr >= 0)
			{
				hr = vtouch->sensor->AccessBodyIndexFrameBuffer(vtouch->depthHeight * vtouch->depthWidth, &vtouch->m_bodyIndexMat.data);
			}
		}
		else if (vtouch->sensorType == SENSOR_PMD)
		{
			// IR �̹����� Color Gray������ ��ü�ϱ� ���� ��ȯ����
			//vtouch->m_infraredMat.convertTo(vtouch->m_grayMatBuffer, CV_8UC1);
		}


		return hr;
	}

	int Core::Initialize()
	{
		if (vtouch)
		{
			return -1;
		}

		vtouch = VTouchData::getInstance();

		cv::setBreakOnError(true);

		// Init sensor & related buffers
		int hr = vtouch->Initialize();
		//readConfig("./bin/config.yml");

		if (hr >= 0)
		{
			// Select algorithm
			/*hr = makeInstanceAlgorithm();

			depthSize[0] = vtouch->depthWidth;
			depthSize[1] = vtouch->depthHeight;*/
		}
		else
		{
			vtouch = 0;
		}

		return hr;
	}

	void Core::MainProc()
	{

		int hr = -1;
		int frame = 0;

		while (is_running)
		{

			hr = vtouch->sensor->UpdateFrame();

			if (hr >= 0)
			{

				hr = GetSensorData();

			}

			if(hr >= 0)
			{
				makeOutImage();
			}

			vtouch->sensor->ReleaseFrame();
		}

	}

	void Core::makeOutImage()
	{

		ushort* depth_data = (ushort*)vtouch->m_depthMat.data;
		uchar* outmat_data = (uchar*)vtouch->m_outMat.data;

		unsigned int depthSize = vtouch->m_depthMat.total();

		for(size_t i = 0 ; i < depthSize; ++i)
		{
			if (depth_data[i])
			{
				uchar p = 200 - int(round(abs(float(depth_data[i] % 1001 - 500) * 0.3F)));
				outmat_data[i * 3 + 0] = outmat_data[i * 3 + 1] = outmat_data[i * 3 + 2] = p;
			}
		}
	}

	int Core::Run()
	{
		if (!vtouch || is_running || thread.valid())
		{
			return -1;
		}

		is_running = true;

#ifdef WIN64
		thread = std::async(RunThread, this);
#else
		thread = std::async(std::launch::async, RunThread, this);
#endif

		return 0;
	}


}

