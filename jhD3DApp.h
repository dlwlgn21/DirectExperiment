#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include <cassert>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <string>

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <limits>
#include <memory>
#include <filesystem>


#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <type_traits>

#include "jhTexture.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

static constexpr const UINT VERTEX_COUNT = 4;
static constexpr const UINT POINT_SAMPLER_SLOT_NUMBER = 0;
static constexpr const UINT DEFAULT_TEXTURE_SLOT_NUMBER = 0;

namespace jh
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT2 UV;
	};

	struct MatrixBuffer
	{
		DirectX::XMMATRIX worldMat;
	};

	class D3DApp final
	{
	public:
		static D3DApp& GetInstance()
		{
			static D3DApp instance;
			return instance;
		}
		D3DApp(const D3DApp& other) = delete;
		D3DApp& operator=(const D3DApp& other) = delete;

		void Initialize(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow);
		void Run();
		void Update();
		void FixedUpdate();
		void RenderFrame();
		void Release();
		
		void WriteDataAtBuffer(ID3D11Resource* pResource, const void* pData, const size_t dataSize);

		bool IfFailedHR(HRESULT hr);

		ID3D11Device* GetDevice() const { return mcpDevice.Get(); }
		ID3D11DeviceContext* GetDeviceContext() const { return mcpDeviceContext.Get(); }
		HWND GetHwnd() const { return mHwnd; }

	private:
		void initializeWindow(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow);
		void initializeDirectX();
		void initializeVertexAndIndexBuffer();
		void createAndSetShaders();
		void createAndSetSamplerState();
		void createAndSetBlendState();
		void createConstantBufferForTransform();

		void initializeInputLayoutAndSetIA();
		void loadTexture();

		__forceinline HWND GetHWND() const { return mHwnd; }
		__forceinline UINT GetScreenWidth() const { return mScreenWidth; }
		__forceinline UINT GetScreenHeight() const { return mScreenHeight; }

	private:
		D3DApp()
			: mScreenWidth()
			, mScreenHeight()
			, mHwnd()
			, mcpDevice(nullptr)
			, mcpDeviceContext(nullptr)
			, mVertices{}
			, mspTexture(std::make_unique<class Texture>())
			, mX(0.0f)
			, mY(0.0f)
			, mZ(0.0f)
		{
		}
		~D3DApp() = default;

	private:
		UINT mScreenWidth;
		UINT mScreenHeight;
		HWND mHwnd;
		HDC	 mHDC;

		Microsoft::WRL::ComPtr<ID3D11Device>			mcpDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		mcpDeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			mcpSwapChain;

		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mcpRenderTargetTextrue;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  mcpRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mcpDepthStencilTextrue;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	mcpDepthStencilView;

		Vertex mVertices[VERTEX_COUNT];
		Microsoft::WRL::ComPtr<ID3D11Buffer>			mcpVertexBuffer;

		Microsoft::WRL::ComPtr<ID3DBlob>				mcpErrorBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpPSBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		mcpVertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		mcpPixelShader;

		Microsoft::WRL::ComPtr<ID3D11InputLayout>		mcpInputLayout;
		

		Microsoft::WRL::ComPtr<ID3D11SamplerState>		mcpPointSampler;
		std::unique_ptr<class Texture>					mspTexture;

		Microsoft::WRL::ComPtr<ID3D11BlendState>		mcpBlendState;

		Microsoft::WRL::ComPtr<ID3D11Buffer>			mcpConstantBuffer;
		float mX;
		float mY;
		float mZ;
		DirectX::XMMATRIX mWorldMat;
	};
}