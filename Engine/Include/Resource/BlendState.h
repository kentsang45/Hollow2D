#pragma once

#include "RenderState.h"

class ENGINE_DLL CBlendState :
	public CRenderState
{
	friend class CResourceManager;

private:
	CBlendState();
	~CBlendState();

private:
	vector<D3D11_RENDER_TARGET_BLEND_DESC>	m_vecDesc;
	float		m_fBlendFactor[4];
	UINT		m_iSampleMask;
	float		m_fPrevBlendFactor[4];
	UINT		m_iPrevSampleMask;

public:
	bool AddBlendDesc(BOOL bBlendEnable = TRUE, D3D11_BLEND eSrc = D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND eDest = D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP eOp = D3D11_BLEND_OP_ADD,
		D3D11_BLEND eSrcAlpha = D3D11_BLEND_ONE, D3D11_BLEND eDestAlpha = D3D11_BLEND_ZERO, D3D11_BLEND_OP eOpAlpha = D3D11_BLEND_OP_ADD,
		UINT8 iWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL);
	bool CreateBlend(BOOL bAlphaCoverage, BOOL bIndependent);

public:
	virtual void SetState();
	virtual void ResetState();
};

