#include "jhD3DApp.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhSceneManager.h"
#include "jhResourceMaker.h"
#include "jhCameraManager.h"
#include "jhCollisionManager.h"
#include "jhMonsterObjectPool.h"
#include "jhLightingManager.h"
#include "jhMonsterUIManager.h"
#include "jhPlayerLevelManager.h"

using namespace DirectX;
using namespace Microsoft::WRL;

namespace jh
{

	void D3DApp::Initialize(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow)
	{
		initializeWindow(className, titleName, screenWidth, screenHeight, hInstance, nCmdShow);
		Time::Initialize();
		Input::Initialize();
		graphics::GraphicDeviceDX11::GetInstance().InitializeDevice(mScreenWidth, mScreenHeight, mHwnd);
		CollisionManager::GetInstance().Initialize();
		ResourceMaker::GetInstance().Initialize();
		PlayerLevelManager::GetInstance().Initialize();
		SceneManager::GetInstance().Initialize();
		LightingManager::GetInstance().Initialize();
		MonsterUIManager::GetInstance().Initialize();
	}
	void D3DApp::initializeWindow(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow)
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;
		RECT wr{ 0, 0, static_cast<LONG>(mScreenWidth), static_cast<LONG>(mScreenHeight) };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

		mHwnd = CreateWindowW(
			className,
			titleName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			wr.right - wr.left,
			wr.bottom - wr.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		if (mHwnd == nullptr)
		{
			assert(false);
		}
		mHDC = GetDC(mHwnd);
		ShowWindow(mHwnd, nCmdShow);
		SetForegroundWindow(mHwnd);
		SetFocus(mHwnd);
		UpdateWindow(mHwnd);
	}

	void D3DApp::Run()
	{
		Update();
		FixedUpdate();
		RenderFrame();
	}
	void D3DApp::Update()
	{
		Time::Update();
		Input::Update();
		CollisionManager::GetInstance().Update();
		SceneManager::GetInstance().Update();
	}
	void D3DApp::FixedUpdate()
	{
		CollisionManager::GetInstance().FixedUpdate();
		SceneManager::GetInstance().FixedUpdate();
	}
	void D3DApp::RenderFrame()
	{
		Time::Render(mHDC);
		graphics::GraphicDeviceDX11::GetInstance().ClearRenderTargetAndDepthStencilView();
		
		MonsterUIManager::GetInstance().WriteMonsterUIDataAtBuffer();
		MonsterUIManager::GetInstance().SetPipeline();

		LightingManager::GetInstance().WriteLightDataAtBuffer();
		LightingManager::GetInstance().SetPipeline();
		
		CameraManager::GetInstance().Render();
		//CollisionManager::GetInstance().Render();

		MonsterUIManager::GetInstance().ClearMonsterUIAttribute();
		LightingManager::GetInstance().ClearLightAttribute();
	}
	void D3DApp::Release()
	{
		SceneManager::GetInstance().Release();
		ResourceMaker::GetInstance().Release();
		graphics::GraphicDeviceDX11::GetInstance().Release();
	}
	void D3DApp::Present()
	{
		graphics::GraphicDeviceDX11::GetInstance().Present();
	}
	bool D3DApp::IfFailedHR(HRESULT hr)
	{
		if (FAILED(hr))
		{
			assert(false);
			return false;
		}
		return true;
	}
}
