#pragma once

#include "RenderState.h"

class ENGINE_DLL CDepthStencilState :
	public CRenderState
{
	friend class CResourceManager;

private:
	CDepthStencilState();
	~CDepthStencilState();

private:
	UINT		m_iStencilRef;
	UINT		m_iPrevStencilRef;

public:
	bool CreateDepthStencil(BOOL bDepthEnable = TRUE, D3D11_DEPTH_WRITE_MASK eDepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
		D3D11_COMPARISON_FUNC eDepthFunc = D3D11_COMPARISON_LESS, BOOL bStencilEnable = FALSE,
		UINT8 iStencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK, UINT8 iStencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK,
		D3D11_DEPTH_STENCILOP_DESC tFrontFace = { D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP , D3D11_COMPARISON_ALWAYS }, 
		D3D11_DEPTH_STENCILOP_DESC tBackFace = { D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP , D3D11_COMPARISON_ALWAYS });

public:
	virtual void SetState();
	virtual void ResetState();
};

