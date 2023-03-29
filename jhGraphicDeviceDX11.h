#pragma once
#include "jhEngine.h"
#include "jhGraphics.h"
#include "jhTexture.h"
#include "jhMesh.h"

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
		void createAndSetShaders();
		void createAndSetSamplerState();
		void createAndSetBlendState();
		void createConstantBufferForTransform();

		void initializeInputLayoutAndSetIA();
		void loadTexture();

	private:
		GraphicDeviceDX11()
			: mspTexture(std::make_unique<Texture>())
			, mspMesh(std::make_unique<Mesh>())
			, mcpDevice()
			, mcpDeviceContext()
			, mcpSwapChain()
			, mcpRenderTargetTextrue()
			, mcpRenderTargetView()
			, mcpDepthStencilTextrue()
			, mcpDepthStencilView()
			, mcpVertexBuffer()
			, mcpErrorBlob()
			, mcpVSBlob()
			, mcpPSBlob()
			, mcpVertexShader()
			, mcpPixelShader()
			, mcpInputLayout()
			, mcpPointSampler()
			, mcpBlendState()
			, mcpConstantBuffer()
			, mX(0.0f)
			, mY(0.0f)
			, mZ(0.0f)
			, mWorldMat()
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

		Microsoft::WRL::ComPtr<ID3DBlob>				mcpErrorBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpPSBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		mcpVertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		mcpPixelShader;

		Microsoft::WRL::ComPtr<ID3D11InputLayout>		mcpInputLayout;


		Microsoft::WRL::ComPtr<ID3D11SamplerState>		mcpPointSampler;
		std::unique_ptr<class Texture>					mspTexture;
		std::unique_ptr<class Mesh>						mspMesh;


		Microsoft::WRL::ComPtr<ID3D11BlendState>		mcpBlendState;

		Microsoft::WRL::ComPtr<ID3D11Buffer>			mcpConstantBuffer;
		float mX;
		float mY;
		float mZ;
		DirectX::XMMATRIX mWorldMat;
	};
}

