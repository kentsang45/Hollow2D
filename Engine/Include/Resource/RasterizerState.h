#pragma once

#include "RenderState.h"

class ENGINE_DLL CRasterizerState :
	public CRenderState
{
	friend class CResourceManager;

private:
	CRasterizerState();
	~CRasterizerState();

public:
	bool CreateRasterizerState(D3D11_FILL_MODE eFillMode = D3D11_FILL_SOLID, 
		D3D11_CULL_MODE eCullMode = D3D11_CULL_BACK, BOOL bFrontCounterClockwise = FALSE, 
		INT iDepthBias = 0, FLOAT fDepthBiasClamp = 0.f, FLOAT fSlopeScaledDepthBias = 0.f,
		BOOL bDepthClipEnable = TRUE, BOOL bScissorEnable = FALSE,
		BOOL bMultisampleEnable = FALSE, BOOL bAntialiasedLineEnable = FALSE);

public:
	virtual void SetState();
	virtual void ResetState();
};

