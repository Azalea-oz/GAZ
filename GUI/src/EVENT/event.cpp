#include"event.hpp"



namespace AZ{
	namespace GUI{
		
		std::wstring CvtMsgCodetowc(UINT msg){
			switch(msg){
				CVTMSGWC(WM_NULL);
				CVTMSGWC(WM_CREATE);
				CVTMSGWC(WM_DESTROY);
				CVTMSGWC(WM_MOVE);
				CVTMSGWC(WM_SIZE);
				CVTMSGWC(WM_ACTIVATE);
				CVTMSGWC(WM_SETFOCUS);
				CVTMSGWC(WM_KILLFOCUS);
				CVTMSGWC(WM_ENABLE);
				CVTMSGWC(WM_SETREDRAW);
				CVTMSGWC(WM_SETTEXT);
				CVTMSGWC(WM_GETTEXT);
				CVTMSGWC(WM_GETTEXTLENGTH);
				CVTMSGWC(WM_PAINT);
				CVTMSGWC(WM_CLOSE);
				CVTMSGWC(WM_QUERYENDSESSION);
				CVTMSGWC(WM_QUIT);
				CVTMSGWC(WM_QUERYOPEN);
				CVTMSGWC(WM_ERASEBKGND);
				CVTMSGWC(WM_SYSCOLORCHANGE);
				CVTMSGWC(WM_ENDSESSION);
				CVTMSGWC(WM_SHOWWINDOW);
				//CVTMSGWC(WM_CTLCOLOR);
				CVTMSGWC(WM_WININICHANGE);
				//CVTMSGWC(WM_SETTINGCHANGE);
				CVTMSGWC(WM_DEVMODECHANGE);
				CVTMSGWC(WM_ACTIVATEAPP);
				CVTMSGWC(WM_FONTCHANGE);
				CVTMSGWC(WM_TIMECHANGE);
				CVTMSGWC(WM_CANCELMODE);
				CVTMSGWC(WM_SETCURSOR);
				CVTMSGWC(WM_MOUSEACTIVATE);
				CVTMSGWC(WM_CHILDACTIVATE);
				CVTMSGWC(WM_QUEUESYNC);
				CVTMSGWC(WM_GETMINMAXINFO);
				CVTMSGWC(WM_PAINTICON);
				CVTMSGWC(WM_ICONERASEBKGND);
				CVTMSGWC(WM_NEXTDLGCTL);
				CVTMSGWC(WM_SPOOLERSTATUS);
				CVTMSGWC(WM_DRAWITEM);
				CVTMSGWC(WM_MEASUREITEM);
				CVTMSGWC(WM_DELETEITEM);
				CVTMSGWC(WM_VKEYTOITEM);
				CVTMSGWC(WM_CHARTOITEM);
				CVTMSGWC(WM_SETFONT);
				CVTMSGWC(WM_GETFONT);
				CVTMSGWC(WM_SETHOTKEY);
				CVTMSGWC(WM_GETHOTKEY);
				CVTMSGWC(WM_QUERYDRAGICON);
				CVTMSGWC(WM_COMPAREITEM);
				CVTMSGWC(WM_GETOBJECT);
				CVTMSGWC(WM_COMPACTING);
				CVTMSGWC(WM_COMMNOTIFY);
				CVTMSGWC(WM_WINDOWPOSCHANGING);
				CVTMSGWC(WM_WINDOWPOSCHANGED);
				CVTMSGWC(WM_POWER);
				//CVTMSGWC(WM_COPYGLOBALDATA);
				CVTMSGWC(WM_COPYDATA);
				CVTMSGWC(WM_CANCELJOURNAL);
				CVTMSGWC(WM_NOTIFY);
				CVTMSGWC(WM_INPUTLANGCHANGEREQUEST);
				CVTMSGWC(WM_INPUTLANGCHANGE);
				CVTMSGWC(WM_TCARD);
				CVTMSGWC(WM_HELP);
				CVTMSGWC(WM_USERCHANGED);
				CVTMSGWC(WM_NOTIFYFORMAT);
				CVTMSGWC(WM_CONTEXTMENU);
				CVTMSGWC(WM_STYLECHANGING);
				CVTMSGWC(WM_STYLECHANGED);
				CVTMSGWC(WM_DISPLAYCHANGE);
				CVTMSGWC(WM_GETICON);
				CVTMSGWC(WM_SETICON);
				CVTMSGWC(WM_NCCREATE);
				CVTMSGWC(WM_NCDESTROY);
				CVTMSGWC(WM_NCCALCSIZE);
				CVTMSGWC(WM_NCHITTEST);
				CVTMSGWC(WM_NCPAINT);
				CVTMSGWC(WM_NCACTIVATE);
				CVTMSGWC(WM_GETDLGCODE);
				CVTMSGWC(WM_SYNCPAINT);
				CVTMSGWC(WM_NCMOUSEMOVE);
				CVTMSGWC(WM_NCLBUTTONDOWN);
				CVTMSGWC(WM_NCLBUTTONUP);
				CVTMSGWC(WM_NCLBUTTONDBLCLK);
				CVTMSGWC(WM_NCRBUTTONDOWN);
				CVTMSGWC(WM_NCRBUTTONUP);
				CVTMSGWC(WM_NCRBUTTONDBLCLK);
				CVTMSGWC(WM_NCMBUTTONDOWN);
				CVTMSGWC(WM_NCMBUTTONUP);
				CVTMSGWC(WM_NCMBUTTONDBLCLK);
				CVTMSGWC(WM_NCXBUTTONDOWN);
				CVTMSGWC(WM_NCXBUTTONUP);
				CVTMSGWC(WM_NCXBUTTONDBLCLK);
				CVTMSGWC(EM_GETSEL);
				
			default:
				return std::to_wstring(msg);
			}
		}
		
	
	}
}