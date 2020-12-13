#include"../AAAZLE.hpp"


class Test : public AZ::GUI::WINDOW{
	HFONT hfont;
	
	HDROP hd;
	HANDLE hfile;
	std::wstring wFileName;
	std::string FileName;
	std::string ReadFS;
	
	RECT rect;
public:
	Test(int w, int h) : WINDOW(w, h){
		ReadFS = "";
		rect.right = w;
		rect.left = 0;
		rect.top = 0;
		rect.bottom = h;
	}
	Test(int w, int h, std::string str) : WINDOW(w, h, str){
		ReadFS = "";
		rect.right = w;
		rect.left = 0;
		rect.top = 0;
		rect.bottom = h;
	}
	Test(int w, int h, std::wstring str) : WINDOW(w, h, str){
		ReadFS = "";
		rect.right = w;
		rect.left = 0;
		rect.top = 0;
		rect.bottom = h;
	}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		DragAcceptFiles(hwnd, true);
		return 0;
	}
	AZ::GUI::CODE EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		char tmp[256];
		switch(msg){
		case WM_DROPFILES:
			
			//Get D&D File.
			hd = (HDROP)wp;
			DragQueryFile(hd, 0, tmp, sizeof(tmp));
			FileName = tmp;
			
			hfile = CreateFile(FileName.c_str(), GENERIC_READ, 0,
				NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if(hfile != INVALID_HANDLE_VALUE){
				char ReadStr[GetFileSize(hfile, NULL)];
				DWORD ReadSize;
				ReadFile(hfile, ReadStr, GetFileSize(hfile, NULL), &ReadSize, NULL);
				ReadFS = ReadStr;
			}
			InvalidateRect(hwnd, NULL, true);
			CloseHandle(hfile);
			DragFinish(hd);
			
		}
		return 0;
	}
	
	AZ::GUI::CODE ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		int result = MessageBox(hwnd, "end", "Confirmation", MB_YESNO);
		if (IDYES != result) return 0;
		return 1;
	}
	AZ::GUI::CODE ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		rect.right = GetSize()[0];
		rect.bottom = GetSize()[1];
		return 0;
	}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		
		
		// ******************************************************************* //
		//Font.DrawString(HDC, char*)
		//Font.DrawString(HDC, std::string)
		//Font.DrawString(HDC, wchar_t)
		//Font.DrawString(HDC, std::wstring)
		
		//Font.Size()
		//Font.Angle()
		//Font.Weight()
		//Font.Italic()
		//Font.UnderLine()
		//Font.StrikeOut()
		//Font.CharSet()
		//Font.Precision()
		//Font.Quality()
		//Font.Family()
		//Font.Pitch()
		//Font.FontName()
		//Font.Create()
		hfont = CreateFont(
			20, 0, 0, 0,
			FW_NORMAL, false, false, false,
			SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			"ＭＳ 明朝");
		
		SelectObject(hdc, hfont);
		
		DRAWTEXTPARAMS dtp;
		dtp.cbSize = sizeof(DRAWTEXTPARAMS);
		dtp.iTabLength = 4;
		dtp.iLeftMargin = 1;
		dtp.iRightMargin = 1;
		
		std::string tmp = std::to_string(GetSize()[0]);
		tmp += " : ";
		tmp += std::to_string(GetSize()[1]);
		tmp += "\n";
		tmp += ReadFS;
		
		DrawTextEx(
			hdc, (LPTSTR)tmp.c_str(), -1, &rect,
			DT_WORDBREAK | DT_NOFULLWIDTHCHARBREAK | DT_EXPANDTABS | DT_TABSTOP, &dtp);
		
		SelectObject(hdc, GetStockObject(SYSTEM_FONT));
		// ******************************************************************* //
		
		
		DeleteObject(hfont);
		EndPaint(hwnd, &ps);
		
		return 0;
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	Test test(700, 500, "フォントテスト");

	test.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"TestWindow").Register();
	test.WindowStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_VSCROLL).WindowPos(0, 0);
	
	
	
	test.Create();
	test.Show(nCmdShow);
	return test.Message();
}