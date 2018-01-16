#pragma once
namespace vt {

	class VTouchData
	{
	public:

		inline static VTouchData* getInstance()
		{

			if (instance == 0) instance = new VTouchData();

			return instance;

		}

		int Initialize();
		void Release();

		// Sensors
		vt::Camera::ISensor* sensor;
		vt::Camera::IMapper* mapper;
		vt::Camera::Intrinsics intrinsic;

		// Image size
		int colorWidth;
		int colorHeight;
		int depthWidth;
		int depthHeight;

		// raw dataset
		cv::Mat m_grayMat;
		cv::Mat m_depthMat;
		cv::Mat m_bodyIndexMat;
		cv::Mat m_worldMat;
		cv::Mat m_infraredMat;
		cv::Mat m_confidenceMat;

		cv::Mat m_outMat;

		int sensorType; // 0: kinect 1: pmd 2: meerae

		int max_user;

	private:
		VTouchData();
		static VTouchData *instance;
	};

}
