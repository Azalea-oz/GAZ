#include"../../src/AAAZLE.hpp"

BOOL DotEllipse(HDC hdc, int X, int Y, int R){
	return Ellipse(hdc, X-R, Y-R, X+R, Y+R);
}

double abs(double x, double y){
	if(x > y) return x - y;
	return y - x;
}

class MAINWINDOW : public AZ::GUI::WINDOW{
	int PixNum;
	int cnt;
	int rate;
public:
	MAINWINDOW(int tmp) : WINDOW(800, 800, L"DOT"){
		PixNum = tmp;
		cnt = 1;
		rate = 1;
	}
	~MAINWINDOW(){}
	
	void countup(){
		if(cnt > 1){
			cnt = 1;
			
			if(rate > 30) rate = 1;
			else rate++;
		}
		else cnt++;
	}
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		int r2 = 800 / PixNum;
		double cen =  PixNum / 2 - 0.5;
		for(int i=0; i < PixNum; i++){
			for(int j=0; j < PixNum; j++){
				DotEllipse(hdc,
					r2 * (i + 0.5),
					r2 * (j + 0.5),
					r2 / 2 * rate * abs(r2 * (i + 0.5), 400) / 400 * abs(r2 * (j + 0.5), 400) / 400
					//400 / PixNum * (1 - abs(cen, i) / cen * abs(cen, j)  / cen)
				);
			}
		}
		
		wchar_t tmp[256];
		wsprintfW(tmp, L"width = %d : height = %d", GetSize()[0], GetSize()[1]);
		TextOutW(hdc, 10, 10, tmp, lstrlenW(tmp));
		
		return STOPEVE;
	}
};