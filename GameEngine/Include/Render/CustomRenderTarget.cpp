#include "CustomRenderTarget.h"
#include "../Device.h"
#include "RenderManager.h"
#include "../Resource/RenderState.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Shader.h"
#include "../Resource/ShaderManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Component/CameraComponent.h"
#include "../Resource/Mesh.h"
#include "../CameraManager.h"


CCustomRenderTarget::CCustomRenderTarget() :
	m_pTargetTex(nullptr),
	m_pTargetSRV(nullptr),
	m_pTargetView(nullptr),
	m_pDepthTex(nullptr),
	m_pDepthView(nullptr),
	m_pShader(nullptr),
	m_pMesh(nullptr),
	m_pLayout(nullptr),
	m_bOnDebug(false),
	m_pOldTargetView(nullptr),
	m_pOldDepthView(nullptr),
	m_pDepthDisable(nullptr)
{
	memset(m_fClearColor, 0, sizeof(float) * 4);
}

CCustomRenderTarget::~CCustomRenderTarget()
{
	SAFE_RELEASE(m_pDepthDisable);
	SAFE_RELEASE(m_pOldDepthView);
	SAFE_RELEASE(m_pOldTargetView);
	SAFE_RELEASE(m_pShader);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTargetView);
	SAFE_RELEASE(m_pTargetSRV);
	SAFE_RELEASE(m_pTargetTex);
	SAFE_RELEASE(m_pDepthView);
	SAFE_RELEASE(m_pDepthTex);
}

ID3D11RenderTargetView * CCustomRenderTarget::GetTargetView() const
{
	return m_pTargetView;
}

ID3D11DepthStencilView * CCustomRenderTarget::GetDepthView() const
{
	return m_pDepthView;
}

IDXGISurface * CCustomRenderTarget::GetTargetSurface() const
{
	IDXGISurface* pSurface = nullptr;

	m_pTargetTex->QueryInterface(IID_PPV_ARGS(&pSurface));

	return pSurface;
}

bool CCustomRenderTarget::CreateRenderTarget(const string & strName,
	DXGI_FORMAT eTargetFmt, const Vector3 & vPos,
	const Vector3 & vScale, const Resolution & tRS,
	DXGI_FORMAT eDepthFmt)
{
	m_vPos = vPos;
	m_vScale = vScale;

	// 타겟용 텍스처 생성
	D3D11_TEXTURE2D_DESC	tDesc = {};
	tDesc.Width = tRS.iWidth;
	tDesc.Height = tRS.iHeight;
	tDesc.MipLevels = 1;
	tDesc.ArraySize = 1;
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	tDesc.Format = eTargetFmt;
	tDesc.Usage = D3D11_USAGE_DEFAULT;
	tDesc.MiscFlags = 0;

	if (FAILED(DEVICE->CreateTexture2D(&tDesc, nullptr, &m_pTargetTex)))
		return false;

	// 만들어진 텍스처로 ShaderResourceView와 TargetView를 생성한다.
	if (FAILED(DEVICE->CreateShaderResourceView(m_pTargetTex,
		nullptr, &m_pTargetSRV)))
		return false;

	if (FAILED(DEVICE->CreateRenderTargetView(m_pTargetTex, nullptr, &m_pTargetView)))
		return false;

	if (eDepthFmt != DXGI_FORMAT_UNKNOWN)
	{
		tDesc.Width = tRS.iWidth;
		tDesc.Height = tRS.iHeight;
		tDesc.ArraySize = 1;
		tDesc.SampleDesc.Count = 1;
		tDesc.SampleDesc.Quality = 0;
		tDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		tDesc.Format = eDepthFmt;
		tDesc.Usage = D3D11_USAGE_DEFAULT;

		if (FAILED(DEVICE->CreateTexture2D(&tDesc, nullptr, &m_pDepthTex)))
			return false;

		if (FAILED(DEVICE->CreateDepthStencilView(m_pDepthTex, nullptr, &m_pDepthView)))
			return false;
	}

	return true;
}

void CCustomRenderTarget::SetClearColor(float fClearColor[4])
{
	memcpy(m_fClearColor, fClearColor, sizeof(float) * 4);
}

void CCustomRenderTarget::SetClearColor(const Vector4 & vColor)
{
	memcpy(m_fClearColor, &vColor, sizeof(Vector4));
}

void CCustomRenderTarget::ONDebug(bool bDebug)
{
	m_bOnDebug = bDebug;

	if (m_bOnDebug)
	{
		m_pDepthDisable = GET_SINGLE(CResourceManager)->FindRenderState(RENDERSTATE_NONEDEPTH);
		m_pShader = GET_SINGLE(CShaderManager)->FindShader(STANDARD_TEX_SHADER);
		m_pMesh = GET_SINGLE(CResourceManager)->FindMesh("TexRect");
		m_pLayout = GET_SINGLE(CShaderManager)->FindInputLayout(POS_UV_LAYOUT);
	}
}

void CCustomRenderTarget::ClearTarget()
{
	CONTEXT->ClearRenderTargetView(m_pTargetView, m_fClearColor);

	if (m_pDepthView)
		CONTEXT->ClearDepthStencilView(m_pDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CCustomRenderTarget::SetTarget()
{
	// 기존 디바이스에 지정되어 있는 타겟뷰와 깊이뷰를 얻어온다.
	CONTEXT->OMGetRenderTargets(1, &m_pOldTargetView, &m_pOldDepthView);

	// 만약 깊이버퍼가 생성 안되어 있을 경우 기존에 지정되어 있던
	// 깊이 버퍼를 그대로 지정한다.
	ID3D11DepthStencilView*	pDepth = m_pOldDepthView;
	if (m_pDepthView)
		pDepth = m_pDepthView;

	CONTEXT->OMSetRenderTargets(1, &m_pTargetView, pDepth);
}

void CCustomRenderTarget::ResetTarget()
{
	// 원래 타겟들로 교체한다.
	CONTEXT->OMSetRenderTargets(1, &m_pOldTargetView, m_pOldDepthView);
	SAFE_RELEASE(m_pOldDepthView);
	SAFE_RELEASE(m_pOldTargetView);
}

void CCustomRenderTarget::Render(float fTime)
{
	if (!m_bOnDebug)
		return;

	TransformCBuffer	tTransform = {};
	Matrix	matPos, matScale;
	matScale.Scaling(m_vScale);
	matPos.Translation(m_vPos);

	CScene*	pScene = GET_SINGLE(CSceneManager)->GetScene();

	CCameraComponent*	pCamera = pScene->GetCameraManager()->GetUICamera();

	Matrix	matView, matProj;
	matView = pCamera->GetViewMatrix();
	matProj = pCamera->GetProjMatrix();

	SAFE_RELEASE(pCamera);

	tTransform.matWorld = matScale * matPos;
	tTransform.matView = matView;
	tTransform.matProj = matProj;
	tTransform.matWV = tTransform.matWorld * matView;
	tTransform.matWVP = tTransform.matWV * matProj;
	tTransform.vMeshSize = Vector3(1.f, 1.f, 0.f);

	tTransform.matWorld.Transpose();
	tTransform.matView.Transpose();
	tTransform.matProj.Transpose();
	tTransform.matWV.Transpose();
	tTransform.matWVP.Transpose();

	GET_SINGLE(CShaderManager)->UpdateCBuffer(TRANSFORM_CBUFFER, &tTransform);

	m_pDepthDisable->SetState();

	CONTEXT->PSSetShaderResources(0, 1, &m_pTargetSRV);

	m_pShader->SetShader();

	CONTEXT->IASetInputLayout(m_pLayout);

	m_pMesh->Render(0, 0);

	m_pDepthDisable->ResetState();

	ID3D11ShaderResourceView*	pSRV = nullptr;
	CONTEXT->PSSetShaderResources(0, 1, &pSRV);
}

void CCustomRenderTarget::RenderFullScreen()
{
	CShader* pFullScreen = GET_SINGLE(CShaderManager)->FindShader(FULLSCREEN_SHADER);

	m_pDepthDisable->SetState();

	CONTEXT->PSSetShaderResources(0, 1, &m_pTargetSRV);

	pFullScreen->SetShader();

	// NULL Buffer로 전체 화면크기의 사각형을 출력한다.
	CONTEXT->IASetInputLayout(nullptr);

	UINT iOffset = 0;
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CONTEXT->IASetVertexBuffers(0, 0, nullptr, 0, &iOffset);
	CONTEXT->IASetIndexBuffer(0, DXGI_FORMAT_UNKNOWN, 0);
	CONTEXT->Draw(4, 0);

	m_pDepthDisable->ResetState();

	ID3D11ShaderResourceView*	pSRV = nullptr;
	CONTEXT->PSSetShaderResources(0, 1, &pSRV);

	SAFE_RELEASE(pFullScreen);
}

void CCustomRenderTarget::SetShader(int iRegister)
{
	CONTEXT->PSSetShaderResources(iRegister, 1, &m_pTargetSRV);
}

void CCustomRenderTarget::ResetShader(int iRegister)
{
	ID3D11ShaderResourceView*	pSRV = nullptr;
	CONTEXT->PSSetShaderResources(iRegister, 1, &pSRV);
}

void CCustomRenderTarget::Save(const TCHAR * pFileName, const string & strPathKey)
{
}
