#include "BlendState.h"
#include "../Device.h"

CBlendState::CBlendState()
{
	memset(m_fBlendFactor, 0, sizeof(float) * 4);
	m_iSampleMask = 0xffffffff;

	m_eRenderStateType = RST_BLEND;
}

CBlendState::~CBlendState()
{
}

bool CBlendState::AddBlendDesc(BOOL bBlendEnable, D3D11_BLEND eSrc, D3D11_BLEND eDest,
	D3D11_BLEND_OP eOp, D3D11_BLEND eSrcAlpha, D3D11_BLEND eDestAlpha,
	D3D11_BLEND_OP eOpAlpha, UINT8 iWriteMask)
{
	D3D11_RENDER_TARGET_BLEND_DESC	tDesc = {};

	tDesc.BlendEnable = bBlendEnable;
	tDesc.SrcBlend = eSrc;
	tDesc.DestBlend = eDest;
	tDesc.BlendOp = eOp;
	tDesc.SrcBlendAlpha = eSrcAlpha;
	tDesc.DestBlendAlpha = eDestAlpha;
	tDesc.BlendOpAlpha = eOpAlpha;
	tDesc.RenderTargetWriteMask = iWriteMask;

	m_vecDesc.push_back(tDesc);

	return true;
}

bool CBlendState::CreateBlend(BOOL bAlphaCoverage, BOOL bIndependent)
{
	D3D11_BLEND_DESC	tDesc = {};

	tDesc.AlphaToCoverageEnable = bAlphaCoverage;
	tDesc.IndependentBlendEnable = bIndependent;
	memcpy(tDesc.RenderTarget, &m_vecDesc[0], 
		sizeof(D3D11_RENDER_TARGET_BLEND_DESC) * m_vecDesc.size());

	if (FAILED(DEVICE->CreateBlendState(&tDesc, (ID3D11BlendState**)&m_pState)))
		return false;

	return true;
}

void CBlendState::SetState()
{
	// 현재 지정된 블렌드 상태를 얻어온다.
	CONTEXT->OMGetBlendState((ID3D11BlendState**)&m_pPrevState, m_fPrevBlendFactor, &m_iPrevSampleMask);

	CONTEXT->OMSetBlendState((ID3D11BlendState*)m_pState, m_fBlendFactor, m_iSampleMask);
}

void CBlendState::ResetState()
{
	CONTEXT->OMSetBlendState((ID3D11BlendState*)m_pPrevState, m_fPrevBlendFactor, m_iPrevSampleMask);
	SAFE_RELEASE(m_pPrevState);
}
