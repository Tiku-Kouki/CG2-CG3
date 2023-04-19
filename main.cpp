#include <Windows.h>
#include<cstdint>



LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,
	WPARAM wparam, LPARAM lparam) {
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg) {

	case WM_DESTROY:

			PostQuitMessage(0);

			return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}






int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	WNDCLASS wc{};
	//
	wc.lpfnWndProc = WindowProc;
	//
	wc.lpszClassName = L"CG2WindowClass";
	//
	wc.hInstance = GetModuleHandle(nullptr);
	//
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//
	RegisterClass(&wc);
	//
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	//ウィンドウサイズを表す構造体にクライアント領域をいれる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };


	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		L"CG2",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);
	//
	ShowWindow(hwnd, SW_SHOW);

	MSG msg{};

	while (msg.message != WM_QUIT) {
		//
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else {

			//出力ウィンドウへの文字出力
			OutputDebugStringA("Hello,DirectX!\n");

		}


	}

	

	return 0;
}
