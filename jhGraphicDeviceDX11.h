#pragma once
#include "jhEngine.h"
#include "jhGraphics.h"
#include "jhTexture.h"
#include "jhMesh.h"
#include "jhShader.h"


static constexpr const UINT VERTEX_COUNT = 4;
static constexpr const UINT POINT_SAMPLER_SLOT_NUMBER = 0;
static constexpr const UINT DEFAULT_TEXTURE_SLOT_NUMBER = 0;

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
		void Update();
		void FixedUpdate();

		void Render();
		void WriteDataAtBuffer(ID3D11Resource* pResource, const void* pData, const size_t dataSize);

		void Release();
	
		
		ID3D11Device* GetDeivce() const { return mcpDevice.Get(); }
		ID3D11DeviceContext* GetDeivceContext() const { return mcpDeviceContext.Get(); }
		
	private:
		bool ifFailedHR(HRESULT hr);
		void initializePipelineAndReources();

		void initializeVertexAndIndexBuffer();
		void createShader();
		void createSamplerState();
		void createConstantBufferForTransform();

		void loadTexture();

	private:
		GraphicDeviceDX11()
			: mspTexture()
			, mspMesh()
			, mspMesh2()
			, mspShader()
			, mcpDevice()
			, mcpDeviceContext()
			, mcpSwapChain()
			, mcpRenderTargetTextrue()
			, mcpRenderTargetView()
			, mcpDepthStencilTextrue()
			, mcpDepthStencilView()
			, mcpVertexBuffer()
			, mcpInputLayout()
			, mcpPointSampler()
			, mScreenWidth(0)
			, mScreenHeight(0)
			, mVertices{}
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

		Vertex mVertices[VERTEX_COUNT];
		Microsoft::WRL::ComPtr<ID3D11Buffer>			mcpVertexBuffer;


		Microsoft::WRL::ComPtr<ID3D11InputLayout>		mcpInputLayout;


		Microsoft::WRL::ComPtr<ID3D11SamplerState>		mcpPointSampler;
		
		std::unique_ptr<class Texture>					mspTexture;
		std::unique_ptr<class Mesh>						mspMesh;
		std::unique_ptr<class Mesh>						mspMesh2;
		std::unique_ptr<class Shader>					mspShader;

	};
}

