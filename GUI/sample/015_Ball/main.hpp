#include"../../src/AAAZLE.hpp"
//#include<windowsx.h>
#define MAX_SIZE_X GetSize()[0]
#define MAX_SIZE_Y GetSize()[1]

#define CENTERX MAX_SIZE_X / 2
#define CENTERY MAX_SIZE_Y / 2

#define SPEED 10

#define COLOR_BASE 100



class MAINWINDOW : public AZ::GUI::WINDOW{
	int BallPos[2];
	int SpeedX;
	int SpeedY;
	int BallSize;
	
	BYTE cr, cg, cb;
	
public:
	MAINWINDOW(std::wstring str, int Width, int Height, int BALLSIZE) : WINDOW(Width, Height, str), SpeedX(SPEED), SpeedY(SPEED * -0.5), BallSize(BALLSIZE), cr(COLOR_BASE), cb(COLOR_BASE), cg(COLOR_BASE){
		WClassName(str);
		BallPos[0] = CENTERX;
		BallPos[1] = CENTERY;
	}
	~MAINWINDOW(){}
	
	void MoveBall(){
		BallPos[0] += SpeedX;
		if(BallPos[0] < 0 + BallSize){
			BallPos[0] = 0 + BallSize;
			SpeedX *= -1;
		} else if(MAX_SIZE_X - BallSize < BallPos[0]){
			BallPos[0] = MAX_SIZE_X - BallSize;
			SpeedX *= -1;
		}
		
		BallPos[1] += SpeedY;
		if(BallPos[1] < 0 + BallSize){
			BallPos[1] = 0 + BallSize;
			SpeedY *= -1;
		} else if(MAX_SIZE_Y - BallSize < BallPos[1]){
			BallPos[1] = MAX_SIZE_Y - BallSize;
			SpeedY *= -1;
		}
		
		++cr;
		if(cr > 0xFF) cr = cr - 0xFF + COLOR_BASE;
		
		cg += 2;
		if(cg > 0xFF) cg = cg - 0xFF + COLOR_BASE;
		
		cb += 3;
		if(cb > 0xFF) cb = cb - 0xFF + COLOR_BASE;
		
	}
	
	void ClearBKG(HDC hdc){
		RECT rect = {0, 0, GetSize()[0], GetSize()[1]};
		
		FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));
	}
	
	void DrawBall(HDC hdc, BYTE R, BYTE G, BYTE B){
		HBRUSH br = CreateSolidBrush(RGB(R, G, B));
		HBRUSH oldbr = (HBRUSH)SelectObject(hdc, br);
		Ellipse(hdc, BallPos[0] - BallSize, BallPos[1] - BallSize, BallPos[0] + BallSize, BallPos[1] + BallSize);
		SelectObject(hdc, oldbr);
		DeleteObject(br);
		
	}
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		ClearBKG(hdc);
		//GET_WPARAM(wp, lp);
		//TextOutW(hdc, 0, 0, std::wstring(L"Hello World").c_str(), std::wstring(L"Hello World").length());
		//TextOutW(hdc, 0, 20, std::wstring(L"こんにちは").c_str(), std::wstring(L"こんにちは").length());
		
		
		DrawBall(hdc, cr, cg, cb);
		
		return 0;
	}
	
	AZ::GUI::CODE ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(msg){
		case WM_SIZE:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::to_wstring(GetSize()[0]) + std::wstring(L" : ") + std::to_wstring(GetSize()[1]));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::to_wstring(LOWORD(lp)) + std::wstring(L" : ") + std::to_wstring(HIWORD(lp)));
			//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, );
			#endif
			
			MoveBall();
			Render(hwnd, WM_PAINT, 0, 0);
			
			break;
		}
		return DEFAULTEVE;
	}
	
	AZ::GUI::CODE CustomMsg(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		/*
		switch(msg){
		case WM_NCCALCSIZE:
			return STOPEVE;
		}
		*/
		return DEFAULTEVE;
	}
	
	
};