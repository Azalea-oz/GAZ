#include <windows.h>
#include <thread>
#include <chrono>
#include <string>
#include <functional>
//フレームレート計算クラス
class FrameRateCalculator {
	long long cnt = 0;
	const int limit = 60;
	std::string fpsStr = "0fps";
	long long time = currentTime();
 
	//現在時刻を取得する関数
	long long currentTime() {
		std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
	}
 
	//フレームレートの計算と結果文字列を構築する
	void updateStr() {
		//fpsを計算し、文字列として保持する
		long long end = currentTime();
		double fpsResult = (double)(1000) / (end - time) * cnt;
		time = end;
		fpsStr = std::to_string(fpsResult) + "fps";
		cnt = 0;
	}
public:
 
	//フレームレート更新メソッド
	std::string* update() {
		cnt++;
		//規定フレーム数になったらフレームレートの更新
		if (limit <= cnt) {
			updateStr();
		}
		return &fpsStr;
	}
};
 
LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0L;
}
 
int WINAPI WinMain(
	HINSTANCE hInstance,      // 現在のインスタンスのハンドル
	HINSTANCE hPrevInstance,  // 以前のインスタンスのハンドル
	LPSTR lpCmdLine,          // コマンドライン
	int nCmdShow              // 表示状態
) {
	HWND hWnd;
	LPCTSTR szclassName = "WinAPITest";
	WNDCLASSEX wcex;
 
	ZeroMemory((LPVOID)&wcex, sizeof(WNDCLASSEX));
 
	//ウィンドウクラスを登録
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szclassName;
	wcex.hIconSm = NULL;
	RegisterClassEx(&wcex);
 
	//ウィンドウ作成
	hWnd = CreateWindowEx(0, szclassName, "Title", WS_OVERLAPPEDWINDOW,
		0, 0,
		300, 100,
		NULL, NULL, hInstance, NULL);
 
 
	//ウィンドウ表示
	ShowWindow(hWnd, SW_SHOW);
 
	//現在時刻をマイクロ秒で取得
	std::function<long long(void)> currentTimeMicro = []() {
		std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
	};
 
	//fps計算用オブジェクト
	FrameRateCalculator fr;
 
	//メッセージループ
	MSG msg = {};
	int cnt = 0;
	HDC hdc = GetDC(hWnd);
 
	//60fpsで動作させる
	int fps = 60;
 
	//現在時刻を取得(1秒=1000000)
	long long end = currentTimeMicro();
 
	//次の更新時間を計算(1秒/フレームレート)
	long long next = end + (1000 * 1000 / fps);
	while (true) {
		//メッセージを取得したら1(true)を返し取得しなかった場合は0(false)を返す
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				//終了メッセージが来たらゲームループから抜ける
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			
			//ゲームの処理を記述
			//DirectXの描画処理などもここに記述する
			//今回はGDIでカウントアップを描画する処理で動作テスト
			cnt++;
			std::string str = std::to_string(cnt);
			const char* result = str.c_str();
			TextOut(hdc, 10, 10, result, str.size());
 
			//重い処理があったとする
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			
			//fps描画
			std::string* fpsStr = fr.update();
			const char* fpsStrResult = fpsStr->c_str();
			TextOut(hdc, 100, 30, fpsStrResult, fpsStr->size());
 
 
 
			//できるだけ60fpsになるようにスレッド待機
			end = currentTimeMicro();
			if (end < next) {
				//更新時間まで待機
				std::this_thread::sleep_for(std::chrono::microseconds(next - end));
 
				//次の更新時間を計算(1秒/フレームレート加算)
				next += (1000 * 1000 / fps);
			} else {
				//更新時間を過ぎた場合は現在時刻から次の更新時間を計算
				next = end + (1000 * 1000 / fps);
			}
		}
	}
	//解放
	ReleaseDC(hWnd, hdc);
}