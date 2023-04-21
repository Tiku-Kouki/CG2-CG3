#include <Windows.h>
#include<cstdint>
#include<string>
#include<format>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<assert.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")


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

std::wstring ConvertString(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), NULL, 0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), &result[0], sizeNeeded);
	return result;
}

std::string ConvertString(const std::wstring& str)
{
	if (str.empty())
	{
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), NULL, 0, NULL, NULL);
	if (sizeNeeded == 0)
	{
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), result.data(), sizeNeeded, NULL, NULL);
	return result;
}
void Log(const std::string& message) {

	OutputDebugStringA(message.c_str());
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
		wc.lpszClassName,      //　利用するクラス名  
		L"CG2",                //　タイトルバーの文字
		WS_OVERLAPPEDWINDOW,   //　よく見るウィンドウスタイル
		CW_USEDEFAULT,         //　表示X座標(Windowsに任せる)
		CW_USEDEFAULT,         //　表示Y座標(Windowsに任せる)
		wrc.right - wrc.left,  //　ウィンドウ横幅
		wrc.bottom - wrc.top,  //　ウィンドウ縦幅
		nullptr,               //　親ウィンドウハンドル
		nullptr,               //　メニューハンドル
		wc.hInstance,          //　インスタンスハンドル
		nullptr                //　オプション
	
	);
	//
	ShowWindow(hwnd, SW_SHOW);

	IDXGIFactory7* dxgiFactory = nullptr;

	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(hr));

	IDXGIAdapter4* useAdapter = nullptr;

	for(UINT i=0;dxgiFactory->EnumAdapterByGpuPreference(i,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,IID_PPV_ARGS(&useAdapter))!=
		DXGI_ERROR_NOT_FOUND;++i){
	
		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));

		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {

			Log(ConvertString(std::format(L"Use Adapater:{}\n", adapterDesc.Description)));

			break;
		}

		useAdapter = nullptr;
	}
	assert(useAdapter != nullptr);

	ID3D12Device* devic = nullptr;

	D3D_FEATURE_LEVEL featureLevels[]={
		D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0
	
	};
	const char* featureLevelsStrings[] = { "12.2","12.1","12.0" };
	
	for (size_t i = 0; i < _countof(featureLevels); ++i) {

		hr = D3D12CreateDevice(useAdapter, featureLevels[i], IID_PPV_ARGS(&devic));

		if (SUCCEEDED(hr)) {

			Log(std::format("FeatureLevel : {}\n", featureLevelsStrings[i]));
			break;
		}
	}
	assert(devic != nullptr);
	Log("complete create D3D12Device!!!\n");


	MSG msg{};
	//ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		//Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			//ゲームの処理

			
		}


	}
	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");
	
	

	return 0;
}
