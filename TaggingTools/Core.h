#pragma once
#include <future>
namespace vt
{
	class Core {
	
	public:
		int GetSensorData();
		int Initialize();
		int Run();
		void MainProc();
		
	private:
		void makeOutImage();

		static void RunThread(Core* core)
		{
			core->MainProc();
		}

		bool is_running;
		std::future<void> thread;
		VTouchData* vtouch;

		

	};
}