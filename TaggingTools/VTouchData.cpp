#include "stdafx.h"
#include "VTouchData.h"

namespace vt {
	VTouchData* VTouchData::instance;

	VTouchData::VTouchData()
		: sensorType(SENSOR_UNKNOWN)
#ifdef WIN64
#endif
	{
		
	}

	int VTouchData::Initialize()
	{

		int hr = -1;
		
		sensor = vt::Camera::GetSensor();
		sensorType = sensor->GetSensorType();

		if (sensorType == SENSOR_KINECT_V2)  //Kinect
		{

			int source = vt::Camera::Source::Depth |
				vt::Camera::Source::Infrared |
				vt::Camera::Source::Body |
				vt::Camera::Source::BodyIndex |
				vt::Camera::Source::Color;

			hr = sensor->Initialize(source);		// [sensor] ÃÊ±âÈ­

			sensor->GetColorFrameSize(&this->colorWidth, &this->colorHeight);
			this->m_grayMat = cv::Mat(this->colorHeight, this->colorWidth, CV_8U);

		}

		if (hr >= 0)
		{
			hr = sensor->GetMapper(&mapper);
			hr = mapper->GetDepthCameraIntrinsics(intrinsic);
			printf("GetDepthCameraIntrinsics %f %f %f %f \n", intrinsic.focal_length_x, intrinsic.focal_length_y, intrinsic.principal_point_x, intrinsic.principal_point_y);
			sensor->GetMaxTrackingUserCount(&max_user);
		}

		if (hr >= 0)
		{
			// Initilize DATA From Camera
			sensor->GetDepthFrameSize(&this->depthWidth, &this->depthHeight);

			this->m_depthMat = cv::Mat(this->depthHeight, this->depthWidth, CV_16U);
			this->m_bodyIndexMat = cv::Mat(this->depthHeight, this->depthWidth, CV_8U);
			this->m_infraredMat = cv::Mat(this->depthHeight, this->depthWidth, CV_16U);
			this->m_worldMat.create(this->depthHeight, this->depthWidth, CV_32FC3);
			this->m_confidenceMat = cv::Mat(this->depthHeight, this->depthWidth, CV_8U);		// only for PMD

			// opencv 2.x
			//this->m_depthMatBuffer = cv::Mat(this->depthHeight, this->depthWidth, CV_16U, NULL);
			//this->m_bodyIndexMatBuffer = cv::Mat(this->depthHeight, this->depthWidth, CV_8U, NULL);
			//this->m_infraredMatBuffer = cv::Mat(this->depthHeight, this->depthWidth, CV_16U, NULL);
			//this->m_worldMatBuffer.create(this->depthHeight, this->depthWidth, CV_32FC3);

			//this->m_depthMatBuffer = cv::Mat(this->depthHeight, this->depthWidth, CV_16U);
			//this->m_bodyIndexMatBuffer = cv::Mat(this->depthHeight, this->depthWidth, CV_8U);
			//this->m_infraredMatBuffer = cv::Mat(this->depthHeight, this->depthWidth, CV_16U);
			//this->m_worldMatBuffer.create(this->depthHeight, this->depthWidth, CV_32FC3);
			//this->m_confidenceBuffer = cv::Mat(this->depthHeight, this->depthWidth, CV_8U);		// only for PMD

		}
		
		return hr;
	}

	void VTouchData::Release()
	{
		if (sensor)
		{
			sensor->Release();
			sensor = 0;
		}

		if (mapper)
		{
			mapper->Release();
			mapper = 0;
		}

#ifdef WIN64
		
#else
		sem_wait(&detection_result_event);
		sem_destroy(&detection_result_event);

		sem_wait(&out_image_event);
		sem_destroy(&out_image_event);

		pthread_mutex_unlock(&detection_result_mutex);
		pthread_mutex_destroy(&detection_result_mutex);

		pthread_mutex_unlock(&out_image_mutex);
		pthread_mutex_destroy(&out_image_mutex);
#endif

	}
}



