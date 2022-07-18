#pragma once

/*
#include <Windows.h>
#include "DXDefines.h"
#include "LWindow.h"
#include "Status.h"
#include "d3dx12.h"
#include "GraphicsData.h"
*/
#include <Windows.h>
#include <D3d12.h>
#include <D3d12SDKLayers.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <wincodec.h>

#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3dcompiler")



#include "D3dx12.h"
#include "LWindow.h"

#include "GraphicsData.h"

//using namespace GData;
using namespace DirectX;
using namespace Microsoft::WRL;
struct Vertex
{
	Vertex(XMFLOAT3 _pos, XMFLOAT2 _texCoord)
	{
		texCoord = _texCoord;
		pos = _pos;
	}
	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};

// this is the structure of our constant buffer.
struct ConstantBufferPerObject 
{
	XMFLOAT4X4 wvpMat;
};
class Graphics
{
public:
	Graphics() = default;
	~Graphics() = default;

	bool OnInit(LWindow& _window);

	void Update();
	void UpdatePipeline();
	void Render();
	void WaitForPreviousFrame();
	void CleanUp();

	//Gets
	ID3D12Device* Device(){return m_pDevice;}
	IDXGISwapChain3* SwapChain(){return m_pSwapChain;}
	ID3D12CommandQueue* CommandQueue() {return m_pCommandQueue;}
	ID3D12DescriptorHeap* RTVDescriptorHeap() {return m_pRTVDescriptorHeap;}
	ID3D12Resource** RenderTargets(){return m_pRenderTargets;}
	ID3D12CommandAllocator** CommandAllocator(){return m_pCommandAllocator;}
	ID3D12GraphicsCommandList* CommandList(){ return m_pCommandList;}
	ID3D12Fence** Fence(){return m_pFence;}
	HANDLE FenceEvent(){return m_fenceEvent;}
	int FrameIndex(){return m_frameIndex;}
	UINT64* FenceValue(){return m_fenceValue;}
private:

	//Pipeline 
	bool InitDevice();
	bool InitCommandQueue();
	bool InitSwapchain(LWindow& _window);
	bool InitRenderTargets();
	bool InitCommandAllocators();
	bool InitCommandList();
	bool InitFence();

	//Drawing
	bool InitRootSignature();
	bool CreatePSO(PSOData& _psoData);
	bool CreateVertexBuffer();
	bool CreateIndexBuffer(int _vBufferSize, ID3D12Resource* _pVBufferUploadHeap);
  bool CreateDepthBuffer(LWindow& _window);

	bool CreatePerObjectConstantBuffer();

	bool InitScene(int _width, int _height);

	bool Test(int _width, int _height, HWND _hwnd);
	//-------

	//For Setting Up The Pipeline
	static const int m_frameBufferCount = 3; // number of buffers we want, 2 for double buffering, 3 for tripple buffering

	IDXGIFactory4* dxgiFactory = nullptr;

	ID3D12Device* m_pDevice = nullptr; // direct3d device

	IDXGISwapChain3* m_pSwapChain = nullptr; // swapchain used to switch between render targets

	ID3D12CommandQueue* m_pCommandQueue = nullptr; // container for command lists

	ID3D12DescriptorHeap* m_pRTVDescriptorHeap = nullptr; // a descriptor heap to hold resources like the render targets

	ID3D12Resource* m_pRenderTargets[m_frameBufferCount]; // number of render targets equal to buffer count

	ID3D12CommandAllocator* m_pCommandAllocator[m_frameBufferCount]; // we want enough allocators for each buffer * number of threads (we only have one thread)

	ID3D12GraphicsCommandList* m_pCommandList = nullptr; // a command list we can record commands into, then execute them to render the frame

	ID3D12Fence* m_pFence[m_frameBufferCount];    // an object that is locked while our command list is being executed by the gpu. We need as many 
																					 //as we have allocators (more if we want to know when the gpu is finished with an asset)

	HANDLE m_fenceEvent; // a handle to an event when our fence is unlocked by the gpu

	UINT64 m_fenceValue[m_frameBufferCount]; // this value is incremented each frame. each fence will have its own value

	int m_frameIndex; // current rtv we are on

	int m_rtvDescriptorSize; // size of the rtv descriptor on the device (all front and back buffers will be the same size)

	//For Drawing
	PSOData m_psoData;
	ID3D12PipelineState* m_pPipelineStateObject; // pso containing a pipeline state

	ID3D12RootSignature* m_pRootSignature; // root signature defines data shaders will access

	D3D12_VIEWPORT m_viewport; // area that output from rasterizer will be stretched to.

	D3D12_RECT m_scissorRect; // the area to draw in. pixels outside that area will not be drawn onto

	ID3D12Resource* m_pVertexBuffer; // a default buffer in GPU memory that we will load vertex data for our triangle into

	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView; // a structure containing a pointer to the vertex data in gpu memory
																						   // the total size of the buffer, and the size of each element (vertex)

	ID3D12Resource* m_pIndexBuffer;
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView; 

	ID3D12Resource* m_pDepthStencilBuffer; // This is the memory for our depth buffer. it will also be used for a stencil buffer in a later tutorial
	ID3D12DescriptorHeap* m_pDSDescriptorHeap; // This is a heap for our depth/stencil buffer descriptor
	
	int m_ConstantBufferPerObjectAlignedSize = (sizeof(ConstantBufferPerObject) + 255) & ~255;

	ConstantBufferPerObject m_cbPerObject; // this is the constant buffer data we will send to the gpu 
																					// (which will be placed in the resource we created above)

	ID3D12Resource* m_pConstantBufferUploadHeaps[m_frameBufferCount]; // this is the memory on the gpu where constant buffers for each frame will be placed

	UINT8* m_pCBVGPUAddress[m_frameBufferCount]; // this is a pointer to each of the constant buffer resource heaps

	XMFLOAT4X4 m_cameraProjMat; // this will store our projection matrix
	XMFLOAT4X4 m_cameraViewMat; // this will store our view matrix

	XMFLOAT4 m_cameraPosition; // this is our cameras position vector
	XMFLOAT4 m_cameraTarget; // a vector describing the point in space our camera is looking at
	XMFLOAT4 m_cameraUp; // the worlds up vector

	XMFLOAT4X4 m_cube1WorldMat; // our first cubes world matrix (transformation matrix)
	XMFLOAT4X4 m_cube1RotMat; // this will keep track of our rotation for the first cube
	XMFLOAT4 m_cube1Position; // our first cubes position in space

	XMFLOAT4X4 m_cube2WorldMat; // our first cubes world matrix (transformation matrix)
	XMFLOAT4X4 m_cube2RotMat; // this will keep track of our rotation for the second cube
	XMFLOAT4 m_cube2PositionOffset; // our second cube will rotate around the first cube, so this is the position offset from the first cube

	int m_numCubeIndices; // the number of indices to draw the cube

	//Texture
	bool CreateTexture();
	ID3D12Resource* textureBuffer; // the resource heap containing our texture

	int LoadImageDataFromFile(BYTE** imageData, D3D12_RESOURCE_DESC& resourceDescription, LPCWSTR filename, int& bytesPerRow);

	DXGI_FORMAT GetDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID);
	WICPixelFormatGUID GetConvertToWICFormat(WICPixelFormatGUID& wicFormatGUID);
	int GetDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat);

	ID3D12DescriptorHeap* mainDescriptorHeap;
	ID3D12Resource* textureBufferUploadHeap;

};

