#include"../../src/AAAZLE.hpp"


#include <thread>
#include <chrono>
#include <string>
#include <queue>

#define SEC std::chrono::seconds
#define MILLI std::chrono::milliseconds
#define MICRO std::chrono::microseconds
#define NANO std::chrono::nanoseconds

template<typename T = SEC>
std::function<long long(void)> CurrentTime = [](){
	std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<T>(d).count();
};


namespace FPS{
	class TIMER{
		LARGE_INTEGER Freq;
	public:
		TIMER(){
			if(QueryPerformanceFrequency(&Freq) == FALSE){
				
			}
		}
	};
}







class FPSC : public AZ::GUI::WINDOW{
	int count;
	
	std::wstring FPSstr;
	std::wstring FrameRateStr;
	std::wstring WorkStr;
	std::wstring FrameStr;
	std::wstring SleepStr;
	std::wstring WaitcStr;
	int FrameRate;
	int waitc;
	double _fps;
	double fps;
	
	std::chrono::system_clock::time_point a, b;
	std::chrono::system_clock::time_point last;
	
	std::chrono::duration<double, std::milli> work_time;
	std::chrono::duration<double, std::milli> sleep_time;
	std::chrono::duration<double, std::milli> frame_time;
public:
	FPSC(int LockFrameRate) : WINDOW(300, 300, std::wstring(L"FPS[") + std::to_wstring(LockFrameRate) + std::wstring(L"]")){
		if(LockFrameRate == 0) FrameRate = 60;
		else FrameRate = LockFrameRate;
		
		count = 0;
		
		FPSstr = L"fps";
		FrameRateStr = L"0";
		FrameRate = LockFrameRate;
		
		a = b = last = std::chrono::system_clock::now();
		
		fps = 1000.0 / FrameRate;
	}
	~FPSC(){}
	
	void CountUp(){
		//DEBUG::DebugConsole::Get_Instance().Log("count up");
		//DEBUG::DebugConsole::Get_Instance().Log((unsigned int)CurrentTime<MICRO>());
		count++;
	}
	
	float GetFPS(){
		return _fps;
	}
	
	void Update(){
		InvalidateRect(GetHandle(), NULL, true);
		UpdateWindow(GetHandle());
	}
	void Calcfps(){
		if(count >= 100){
			
			a = std::chrono::system_clock::now();
			std::chrono::duration<double, std::micro> delta = a - last;
			
			_fps = (double)(1000.0 * count / delta.count()) * 1000.0;
			count = 0;
			last = std::chrono::system_clock::now();
			WorkStr = std::to_wstring(work_time.count());
			FrameStr = std::to_wstring(frame_time.count());
			SleepStr = std::to_wstring(sleep_time.count());
			WaitcStr = std::to_wstring(waitc);
			//FrameRateStr = std::to_wstring(GetFPS());
		}
	}
	
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		FrameRateStr = std::to_wstring(GetFPS());
		TextOutW(hdc, 5, 10, std::wstring(L"FPS   : ").c_str(), std::wstring(L"FPS   : ").length());
		TextOutW(hdc, 70, 10, (FrameRateStr + FPSstr).c_str(), (FrameRateStr + FPSstr).length());
		
		//TextOutW(hdc, 5, 30, std::wstring(L"cnt   : ").c_str(), std::wstring(L"cnt   : ").length());
		//TextOutW(hdc, 70, 30, std::to_wstring(count).c_str(), std::to_wstring(count).length());
		
		TextOutW(hdc, 5, 50, std::wstring(L"rate  : ").c_str(), std::wstring(L"rate  : ").length());
		TextOutW(hdc, 70, 50, std::to_wstring(fps).c_str(), std::to_wstring(fps).length());
		
		TextOutW(hdc, 5, 90, std::wstring(L"work  : ").c_str(), std::wstring(L"work  : ").length());
		TextOutW(hdc, 70, 90, WorkStr.c_str(), WorkStr.length());
		
		TextOutW(hdc, 5, 130, std::wstring(L"sleep : ").c_str(), std::wstring(L"sleep : ").length());
		TextOutW(hdc, 70, 130, SleepStr.c_str(), SleepStr.length());
		
		TextOutW(hdc, 5, 170, std::wstring(L"frame : ").c_str(), std::wstring(L"frame : ").length());
		TextOutW(hdc, 70, 170, FrameStr.c_str(), FrameStr.length());
		
		TextOutW(hdc, 5, 210, std::wstring(L"waitc : ").c_str(), std::wstring(L"waitc : ").length());
		TextOutW(hdc, 70, 210, WaitcStr.c_str(), WaitcStr.length());
		
		return 0;
	}
	
	
	void testWait(){
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
		a = std::chrono::system_clock::now();
		work_time = a - b;
		waitc = 0;
		if(work_time.count() < fps){
			sleep_time = std::chrono::duration<double, std::milli>((fps - work_time.count()));
			auto msec = std::chrono::duration<double, std::milli>(1);
			timeBeginPeriod(1);
			while(sleep_time.count() >= msec.count()){
				//std::this_thread::sleep_for(std::chrono::microseconds(999));
				Sleep(1);
				std::chrono::duration<double, std::milli> tmp = std::chrono::system_clock::now() - b;
				sleep_time = std::chrono::duration<double, std::milli>((fps - tmp.count()));
				waitc++;
				//std::this_thread::sleep_for(std::chrono::microseconds(std::chrono::duration_cast<std::chrono::milliseconds>(sleep_time).count()));
				//std::this_thread::sleep_for(std::chrono::milliseconds(10));
				//std::this_thread::sleep_for(std::chrono::microseconds(1000));
			}
			timeEndPeriod(1);
		}
		b = std::chrono::system_clock::now();
		frame_time = b - a;
	}
	
	
};