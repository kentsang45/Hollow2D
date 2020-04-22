#pragma once

#include "../GameEngine.h"

class ENGINE_DLL CCustomRenderTarget
{
	friend class CRenderManager;

private:
	CCustomRenderTarget();
	~CCustomRenderTarget();

private:
	ID3D11RenderTargetView*		m_pTargetView;
	ID3D11Texture2D*			m_pTargetTex;
	ID3D11ShaderResourceView*	m_pTargetSRV;
	ID3D11RenderTargetView*		m_pOldTargetView;
	ID3D11DepthStencilView*		m_pDepthView;
	ID3D11Texture2D*			m_pDepthTex;
	ID3D11DepthStencilView*		m_pOldDepthView;
	bool						m_bOnDebug;
	float						m_fClearColor[4];

	class CShader*				m_pShader;
	class CMesh*				m_pMesh;
	ID3D11InputLayout*			m_pLayout;
	class CRenderState*			m_pDepthDisable;
	Vector3						m_vPos;
	Vector3						m_vScale;

public:
	ID3D11RenderTargetView* GetTargetView()	const;
	ID3D11DepthStencilView* GetDepthView()	const;
	IDXGISurface* GetTargetSurface() const;

public:
	bool CreateRenderTarget(const string& strName, DXGI_FORMAT eTargetFmt,
		const Vector3& vPos, const Vector3& vScale,
		const Resolution& tRS,
		DXGI_FORMAT eDepthFmt = DXGI_FORMAT_UNKNOWN);
	void SetClearColor(float fClearColor[4]);
	void SetClearColor(const Vector4& vColor);
	void ONDebug(bool bDebug);
	void ClearTarget();
	void SetTarget();
	void ResetTarget();
	void Render(float fTime);
	void RenderFullScreen();
	void SetShader(int iRegister);
	void ResetShader(int iRegister);
	void Save(const TCHAR* pFileName, const string& strPathKey);
};

