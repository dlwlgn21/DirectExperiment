#pragma once
#include "jhEngine.h"
#include "jhGraphics.h"

namespace jh::graphics
{
	class GraphicDeviceDX11 final
	{
	public:
		static GraphicDeviceDX11& GetInstance()
		{
			static GraphicDeviceDX11 instance;
			return instance;
		}
		GraphicDeviceDX11(const GraphicDeviceDX11& other) = delete;
		GraphicDeviceDX11& operator=(const GraphicDeviceDX11& other) = delete;


		void InitializeDevice(const UINT screenWidth, const UINT screenHeight, HWND hwnd);
		void ClearRenderTargetAndDepthStencilView();
		void Render();

		void WriteDataAtBuffer(ID3D11Resource* pResource, const void* pData, const size_t dataSize);

		void Release();
	
		
		ID3D11Device* GetDeivce() const { return mcpDevice.Get(); }
		ID3D11DeviceContext* GetDeivceContext() const { return mcpDeviceContext.Get(); }
		
	private:
		bool ifFailedHR(HRESULT hr);

	private:
		GraphicDeviceDX11()
			: mcpDevice()
			, mcpDeviceContext()
			, mcpSwapChain()
			, mcpRenderTargetTextrue()
			, mcpRenderTargetView()
			, mcpDepthStencilTextrue()
			, mcpDepthStencilView()
			, mcpVertexBuffer()
			, mcpInputLayout()
			, mScreenWidth(0)
			, mScreenHeight(0)
		{

		}
		~GraphicDeviceDX11() = default;

	private:
		UINT mScreenWidth;
		UINT mScreenHeight;


		Microsoft::WRL::ComPtr<ID3D11Device>			mcpDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		mcpDeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			mcpSwapChain;

		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mcpRenderTargetTextrue;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  mcpRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mcpDepthStencilTextrue;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	mcpDepthStencilView;

		Microsoft::WRL::ComPtr<ID3D11Buffer>			mcpVertexBuffer;


		Microsoft::WRL::ComPtr<ID3D11InputLayout>		mcpInputLayout;

	};
}

