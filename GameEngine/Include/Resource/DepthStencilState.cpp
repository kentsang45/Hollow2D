
#include "DepthStencilState.h"
#include "../Device.h"

CDepthStencilState::CDepthStencilState()
{
	m_iStencilRef	= 0xffffffff;

	m_eRenderStateType = RST_DEPTH;
}

CDepthStencilState::~CDepthStencilState()
{
}

bool CDepthStencilState::CreateDepthStencil(BOOL bDepthEnable, D3D11_DEPTH_WRITE_MASK eDepthWriteMask,
	D3D11_COMPARISON_FUNC eDepthFunc, BOOL bStencilEnable, UINT8 iStencilReadMask, 
	UINT8 iStencilWriteMask, D3D11_DEPTH_STENCILOP_DESC tFrontFace, 
	D3D11_DEPTH_STENCILOP_DESC tBackFace)
{
	D3D11_DEPTH_STENCIL_DESC	tDesc = {};

	tDesc.DepthEnable = bDepthEnable;
	tDesc.DepthWriteMask = eDepthWriteMask;
	tDesc.DepthFunc = eDepthFunc;
	tDesc.StencilEnable = bStencilEnable;
	tDesc.StencilReadMask = iStencilReadMask;
	tDesc.StencilWriteMask = iStencilWriteMask;
	tDesc.FrontFace = tFrontFace;
	tDesc.BackFace = tBackFace;

	if(FAILED(DEVICE->CreateDepthStencilState(&tDesc, (ID3D11DepthStencilState**)&m_pState)))
		return false;

	return true;
}

void CDepthStencilState::SetState()
{
	// 현재 지정된 블렌드 상태를 얻어온다.
	CONTEXT->OMGetDepthStencilState((ID3D11DepthStencilState**)&m_pPrevState, &m_iPrevStencilRef);

	CONTEXT->OMSetDepthStencilState((ID3D11DepthStencilState*)m_pState, m_iStencilRef);
}

void CDepthStencilState::ResetState()
{
	CONTEXT->OMSetDepthStencilState((ID3D11DepthStencilState*)m_pPrevState, m_iPrevStencilRef);
	SAFE_RELEASE(m_pPrevState);
}

