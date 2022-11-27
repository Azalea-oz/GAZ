#include"../../src/AAAZLE.hpp"
#include<windowsx.h>
#include<stdio.h>

#define TITLE1 L"HTML Editor ["
#define TITLE2 L"]"

#define ID_EDIT_AREA 100001
#define ID_TEST_BUTTON 100002
#define IDM_BASICINPUT 100201
#define IDM_SAVE 100202
#define IDM_SAVES 100203
#define IDM_NEW 100204


class HTMLEDIT : public AZ::GUI::WINDOW{
	
public:
	HTMLEDIT() : WINDOW(500, 500, L"EDIT"){
		SetExStyle(WS_EX_ACCEPTFILES);
	}
	~HTMLEDIT(){}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		
		Rectangle(hdc, 0, 0, GetSize()[0], GetSize()[1]);
		
		return DEFAULTEVE;
	}
	
	AZ::GUI::CODE EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		MessageBoxW(NULL, L"HTMLEDIT", L"File", MB_OK);
		SendMessage(GetTopParent().GetHandle(), msg, wp, lp);
		return STOPEVE;
	}
};

class AZBTN : public AZ::GUI::WINDOW{
	
public:
	AZBTN() : WINDOW(100, 50, L"TEST_BUTTON"){
		WindowPos(50, 50);
		//SetExStyle(WS_EX_ACCEPTFILES);
	}
	AZ::GUI::CODE EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		//SendMessage(GetTopParent().GetHandle(), msg, wp, lp);
		MessageBoxW(NULL, L"AZBTN", L"File", MB_OK);
		return STOPEVE;
	}
};


class AZEDITOR : public AZ::GUI::WINDOW{
	HTMLEDIT EditArea;
	AZBTN button;
public:
	AZEDITOR(std::wstring str) : WINDOW(500, 500, str){
		WClassName(L"Not Selected");
		SetExStyle(WS_EX_ACCEPTFILES);
		
		
		EditArea.WClassName(L"EDIT");
		EditArea.SetWindowStyle(
			/*WS_CHILD | */WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN |
			ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL);
		//Child(EditArea, (HMENU)ID_EDIT_AREA);
		
		button.WClassName(L"BUTTON");
		button.SetWindowStyle(
			WS_CHILD | WS_VISIBLE);
		//Child(button, (HMENU)ID_TEST_BUTTON);
		
	}
	~AZEDITOR(){}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		// Change title name
		//ChangeTitle(std::wstring(TITLE1) + ClippingFileName + std::wstring(TITLE2));
		EditArea.Create();
		
		SetFocus(EditArea.GetHandle());
		
		
		SetWindowTextW(EditArea.GetHandle(), L"Enter HTML Source");
		SendMessage(EditArea.GetHandle(), EM_SETMODIFY, (WPARAM)true, 0);
		//MessageBoxW(NULL, L"AZEDITOR", L"File", MB_OK);
		return STOPEVE;
	}
	
	AZ::GUI::CODE ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		MoveWindow(EditArea.GetHandle(), 0, 0, LOWORD(lp), HIWORD(lp), true);
		return STOPEVE;
	}
	
	AZ::GUI::CODE ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(wp){
		case IDM_END:
			SendMessage(GetParentHandle(), WM_CLOSE, 0, 0);
			break;
		case IDM_BASICINPUT:
		case IDM_SAVES:
		case IDM_NEW:
		case IDM_SAVE:
			break;
		}
		return STOPEVE;
	}
	
	AZ::GUI::CODE EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		MessageBoxW(NULL, L"AZEDITOR", L"File", MB_OK);
		DWORD ReadSize;
		HDROP hdrop = (HDROP)wp;
		std::wstring ClippingFileName;
		std::wstring ClippingText;
		
		wchar_t FileName[256];
		if(DragQueryFileW(hdrop, -1, nullptr, 0) > 1){
			MessageBoxW(GetHandle(), L"Can not open File", L"Error", MB_OK);
		} else{
			DragQueryFileW(hdrop, 0, FileName, 256);
			
			ClippingFileName = FileName;
			FILE *fp;
			if(_wfopen_s(&fp, ClippingFileName.c_str(), L"r, ccs=UTF-8")){
				MessageBoxW(GetHandle(), L"fopen err", L"error", MB_OK);
			}
			wchar_t *tmp = new wchar_t[256];
			while(fgetws(tmp, 256, fp)){
				ClippingText += tmp;
				if(ClippingText.back() == L'\n'){
					ClippingText.pop_back();
					ClippingText += L"\r\n";
				}
			}
			
			SetWindowTextW(EditArea.GetHandle(), ClippingText.c_str());
			
			fclose(fp);
			delete[] tmp;
			
			ChangeTitle(std::wstring(TITLE1) + ClippingFileName + std::wstring(TITLE2));
		}
		
		DragFinish(hdrop);
		
		InvalidateRect(GetHandle() , NULL , TRUE);
		UpdateWindow(GetHandle());
		return STOPEVE;
	}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		
		Rectangle(hdc, 0, 0, GetSize()[0], GetSize()[1]);
		
		return DEFAULTEVE;
	}
};

class AZTEST : public AZ::GUI::WINDOW{
	AZEDITOR azedi1, azedi2;
public:
	AZTEST(std::wstring str) : WINDOW(1000, 1000, str), azedi1(L"test1"), azedi2(L"test2"){
		WClassName(L"Not Selected");
		SetExStyle(WS_EX_ACCEPTFILES);
		
		
		azedi1.WClassName(L"Not Selected");
		//azedi1.SetWindowStyle(/*WS_CHILD | */);
		//Child(EditArea, (HMENU)ID_EDIT_AREA);
		
		azedi2.WClassName(L"Not Selected");
		//azedi1.SetWindowStyle(/*WS_CHILD | */);
		//Child(EditArea, (HMENU)ID_EDIT_AREA);
		
		azedi1.Register();
	}
	~AZTEST(){}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		// Change title name
		//ChangeTitle(std::wstring(TITLE1) + ClippingFileName + std::wstring(TITLE2));
		azedi1.Create();
		azedi2.Create();
		
		return STOPEVE;
	}
	
	
	AZ::GUI::CODE EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		MessageBoxW(NULL, L"AZEDITOR", L"File", MB_OK);
		SendMessage(azedi1.GetHandle(), msg, wp, lp);
		return STOPEVE;
	}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		
		Rectangle(hdc, 0, 0, GetSize()[0], GetSize()[1]);
		
		return DEFAULTEVE;
	}
};

