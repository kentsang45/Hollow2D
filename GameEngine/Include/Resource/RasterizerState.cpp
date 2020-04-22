
#include "RasterizerState.h"
#include "../Device.h"

CRasterizerState::CRasterizerState()
{
	m_eRenderStateType = RST_RASTERIZER;
}

CRasterizerState::~CRasterizerState()
{
}

bool CRasterizerState::CreateRasterizerState(D3D11_FILL_MODE eFillMode, D3D11_CULL_MODE eCullMode,
	BOOL bFrontCounterClockwise, INT iDepthBias, FLOAT fDepthBiasClamp, FLOAT fSlopeScaledDepthBias,
	BOOL bDepthClipEnable, BOOL bScissorEnable, BOOL bMultisampleEnable, BOOL bAntialiasedLineEnable)
{
	D3D11_RASTERIZER_DESC	tDesc	= {};

	tDesc.FillMode = eFillMode;
	tDesc.CullMode = eCullMode;
	tDesc.FrontCounterClockwise = bFrontCounterClockwise;
	tDesc.DepthBias = iDepthBias;
	tDesc.DepthBiasClamp = fDepthBiasClamp;
	tDesc.SlopeScaledDepthBias = fSlopeScaledDepthBias;
	tDesc.DepthClipEnable = bDepthClipEnable;
	tDesc.ScissorEnable = bScissorEnable;
	tDesc.MultisampleEnable = bMultisampleEnable;
	tDesc.AntialiasedLineEnable = bAntialiasedLineEnable;

	if (FAILED(DEVICE->CreateRasterizerState(&tDesc, (ID3D11RasterizerState**)&m_pState)))
		return false;

	return true;
}

void CRasterizerState::SetState()
{
	// 현재 지정된 블렌드 상태를 얻어온다.
	CONTEXT->RSGetState((ID3D11RasterizerState**)&m_pPrevState);

	CONTEXT->RSSetState((ID3D11RasterizerState*)m_pState);
}

void CRasterizerState::ResetState()
{
	CONTEXT->RSSetState((ID3D11RasterizerState*)m_pPrevState);
	SAFE_RELEASE(m_pPrevState);
}

