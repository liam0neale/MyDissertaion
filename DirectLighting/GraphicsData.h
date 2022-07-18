#pragma once
#pragma once
#include "DXDefines.h"

struct PSOData
{
	ID3D12RootSignature* m_pRootSignature;
	D3D12_INPUT_LAYOUT_DESC* inputLayoutDesc;
	D3D12_SHADER_BYTECODE* vertexShaderBytecode;
	D3D12_SHADER_BYTECODE* pixelShaderBytecode;
	DXGI_SAMPLE_DESC* sampleDesc;
};