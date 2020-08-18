#include"time.hpp"

namespace Time{
	void NowTime(){
		time_t t = time(0);
		tm *now = localtime(&t);
		std::cout << "[" << now->tm_year + 1900
				  << "/" << now->tm_mon + 1
				  << "/" << now->tm_mday
				  << " " << now->tm_hour
				  << ":" << now->tm_min
				  << ":" << now->tm_sec << "]" << " ";
	}
}